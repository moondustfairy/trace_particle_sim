#include "../include/action.hh"
#include "run_action.hh"
#include "tracking_action.hh"

MyActionInitialization::MyActionInitialization() : G4VUserActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const {
	SetUserAction(new RunAction());
}

void MyActionInitialization::Build() const
{
	SetUserAction(new RunAction());
	SetUserAction(new MyPrimaryGenerator);
	SetUserAction(new TrackingAction());
}
