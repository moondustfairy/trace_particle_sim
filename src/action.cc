#include "../include/action.hh"

#include "event_action.hh"
#include "run_action.hh"

MyActionInitialization::MyActionInitialization() : G4VUserActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const {
	SetUserAction(new RunAction());
}

void MyActionInitialization::Build() const
{
	SetUserAction(new MyPrimaryGenerator);
	SetUserAction(new RunAction());
	SetUserAction(new EventAction());
}
