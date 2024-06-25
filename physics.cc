#include "physics.hh"

// Geant4 physics headers
#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4IonPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4SystemOfUnits.hh" // Include necessary header for units

MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList()
{
    // Register essential physics processes for secondary electron emission
    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4StepLimiterPhysics());
    RegisterPhysics(new G4EmExtraPhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC());
    RegisterPhysics(new G4IonPhysics());
    RegisterPhysics(new G4StoppingPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::SetCuts()
{
    G4double lowEnergyCut = 0.1 * CLHEP::um; // Use CLHEP::um for the unit
    SetCutValue(lowEnergyCut, "gamma");
    SetCutValue(lowEnergyCut, "e-");
    SetCutValue(lowEnergyCut, "e+");
    SetCutValue(lowEnergyCut, "proton");
}