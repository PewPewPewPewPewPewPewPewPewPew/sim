#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "Randomize.hh" // Include this header for random number generation

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    // Define particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "proton";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

    // Set particle properties
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(1 * MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Define the particle bombarding area + offset
    G4double box_size = 31.5 * um;
    G4double x_center_shift = -1.5 * um;
    G4double y_center_shift = -1.5 * um;
    G4double z_position = 45.0 * um; // Fixed Z position

    // Generate random X and Y positions within the box
    G4double x_position = (G4UniformRand() - 0.5) * box_size + x_center_shift;
    G4double y_position = (G4UniformRand() - 0.5) * box_size + y_center_shift;

    // Set the particle position
    fParticleGun->SetParticlePosition(G4ThreeVector(x_position, y_position, z_position));

    // Generate the primary vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
