#include "SensitiveDetector.hh"
#include "Hit.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackStatus.hh"
#include "G4HCofThisEvent.hh"
#include "G4AnalysisManager.hh"
#include "G4VProcess.hh"  // Include the G4VProcess header

// Constructor
SensitiveDetector::SensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name)
{
    collectionName.insert("HitsCollection");
}

// Destructor
SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new G4THitsCollection<class Hit>(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hce->AddHitsCollection(hcID, fHitsCollection);
    fProtonHits.clear();
    fElectronHits.clear();
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/)
{
    G4Track* track = step->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();
    G4String particleName = particle->GetParticleName();

    // Filter for specific particles (proton and electron)
    if (particleName == "proton" || particleName == "e-")
    {
        // Create a new hit
        class Hit* hit = new class Hit();
        hit->SetEdep(step->GetTotalEnergyDeposit());
        hit->SetPos(step->GetPreStepPoint()->GetPosition());
        hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());
        hit->SetTrackID(track->GetTrackID());
        hit->SetParticleName(particleName);
        hit->SetKineticEnergy(track->GetKineticEnergy());
        hit->SetMomentum(track->GetMomentum());

        // Get next volume name
        G4String nextVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
        hit->SetNextVolumeName(nextVolume);

        // Add hit to collection
        fHitsCollection->insert(hit);

        // Store hit in appropriate vector
        if (particleName == "proton") {
            fProtonHits.push_back(hit);
        } else if (particleName == "e-") {
            fElectronHits.push_back(hit);
        }

        // Output particle information (optional)
        G4cout << "Particle " << particleName << " detected at "
               << hit->GetPos() << " with energy deposition "
               << hit->GetEdep() << " at time "
               << hit->GetTime() << G4endl;

        // Print full track information (optional)
        G4cout << "Track ID: " << track->GetTrackID() << G4endl;
        G4cout << "Particle Name: " << particleName << G4endl;
        G4cout << "Kinetic Energy: " << track->GetKineticEnergy() / MeV << " MeV" << G4endl;
        G4cout << "Momentum: " << track->GetMomentum() / MeV << " MeV" << G4endl;
        G4cout << "Position: " << track->GetPosition() / um << " um" << G4endl;
        G4cout << "Global Time: " << track->GetGlobalTime() / ns << " ns" << G4endl;

        // Kill the particle
        track->SetTrackStatus(fStopAndKill);

        // Confirm track status change (optional)
        if (track->GetTrackStatus() == fStopAndKill) {
            G4cout << "Track for particle *" << particleName << "* is set to be killed." << G4endl;
        }
    }

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
    // Print all hits for the event
    G4int nofHits = fHitsCollection->entries();
    G4int nofProtonHits = 0;
    G4int nofElectronHits = 0;

    G4cout << G4endl
           << "-------->Hits Collection: in this event there are --" << nofHits 
           << "-- hits in the detectors: " << G4endl;

    for (G4int i = 0; i < nofHits; i++) {
        class Hit* hit = (*fHitsCollection)[i];
        hit->Print();
        if (hit->GetParticleName() == "proton") {
            nofProtonHits++;
        } else if (hit->GetParticleName() == "e-") {
            nofElectronHits++;
        }
    }

    G4cout << "Number of *PROTON* hits: " << nofProtonHits << G4endl;
    G4cout << "Number of *ELECTRON* hits: " << nofElectronHits << G4endl;

    G4AnalysisManager* man = G4AnalysisManager::Instance();

    // Save proton hits
    for (const auto& hit : fProtonHits) {
        man->FillNtupleDColumn(0, hit->GetPos().z());
        man->FillNtupleDColumn(1, hit->GetKineticEnergy());
        man->FillNtupleSColumn(2, "proton");
        man->FillNtupleSColumn(3, hit->GetNextVolumeName());
        man->AddNtupleRow();
    }

    // Save electron hits
    for (const auto& hit : fElectronHits) {
        man->FillNtupleDColumn(0, hit->GetPos().z());
        man->FillNtupleDColumn(1, hit->GetKineticEnergy());
        man->FillNtupleSColumn(2, "electron");
        man->FillNtupleSColumn(3, hit->GetNextVolumeName());
        man->AddNtupleRow();
    }
}
