#include "Run.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
    : G4UserRunAction(),
      fProtonHits(0),
      fElectronHits(0) {}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->OpenFile("Output.root"); 
}

void RunAction::EndOfRunAction(const G4Run*) {
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    // Add accumulated hits to ntuple
    man->CreateNtuple("ntuple1", "Summary");
    man->CreateNtupleIColumn("ProtonHits");
    man->CreateNtupleIColumn("ElectronHits");
    man->FinishNtuple();
    man->FillNtupleIColumn(0, fProtonHits);
    man->FillNtupleIColumn(1, fElectronHits);
    man->AddNtupleRow();

    man->Write();
    man->CloseFile();
}

void RunAction::AddProtonHit() {
    fProtonHits++;
}

void RunAction::AddElectronHit() {
    fElectronHits++;
}
