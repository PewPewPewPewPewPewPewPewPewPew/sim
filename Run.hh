#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;

    void AddProtonHit();
    void AddElectronHit();

private:
    G4int fProtonHits;
    G4int fElectronHits;
};

#endif
