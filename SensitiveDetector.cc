#include "SensitiveDetector.hh"
#include "Hit.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackStatus.hh"

SensitiveDetector::SensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name)
{
    collectionName.insert("HitsCollection");
}

SensitiveDetector::~SensitiveDetector()
{}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    G4Track* track = step->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();

    G4String particleName = particle->GetParticleName();

    if (particleName == "proton" || particleName == "e-")
    {
        // Specify that Hit is a class
        class Hit* hit = new class Hit();
        hit->SetEdep(step->GetTotalEnergyDeposit());
        hit->SetPos(step->GetPreStepPoint()->GetPosition());
        hit->SetTime(step->GetPreStepPoint()->GetGlobalTime());
        hit->SetTrackID(track->GetTrackID());

        fHitsCollection->insert(hit);

        // Debugging output
        G4cout << "Particle " << particleName << " detected at "
               << hit->GetPos() << " with energy deposition "
               << hit->GetEdep() << " at time "
               << hit->GetTime() << G4endl;

        // Kill the track
        track->SetTrackStatus(fStopAndKill);

        // Additional check to confirm the track status change
        if (track->GetTrackStatus() == fStopAndKill) {
            G4cout << "Track for particle " << particleName << " is set to be killed." << G4endl;
        }
    }

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce)
{
    // Code to finalize event processing
    // For example, you can output the collected hits here or save them
}