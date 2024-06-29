#include "action.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());

    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
}

