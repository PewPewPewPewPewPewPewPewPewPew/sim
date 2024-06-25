#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"

#include "FTFP_BERT.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "PrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // Run manager
    G4MTRunManager* runManager = new G4MTRunManager();

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    //runManager->SetUserInitialization(new FTFP_BERT);

    // Set user action initialization
    runManager->SetUserInitialization(new ActionInitialization());
    runManager->SetVerboseLevel(2);

    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Set macro path and execute initialization macro if in interactive mode
    if (ui) {
        UImanager->ApplyCommand("/control/macroPath /Users/geant4/Documents/GEANT/geant4-v11.2.1/sim");
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        // Batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Job termination
    delete visManager;
    delete runManager;

    return 0;
}
