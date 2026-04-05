#include "../include/action.hh"

#include "event_action.hh"
#include "histo_manager.hh"
#include "run_action.hh"

MyActionInitialization::MyActionInitialization() : G4VUserActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const {
	// Histo manager
	auto histo = new HistoManager();

	// Actions
	SetUserAction(new RunAction(histo));
}

void MyActionInitialization::Build() const
{
	// Histo manager
	auto histo = new HistoManager();

	// Actions
	//
	SetUserAction(new MyPrimaryGenerator());

	auto runAction = new RunAction(histo);
	SetUserAction(runAction);

	auto eventAction = new EventAction(runAction, histo);
	SetUserAction(eventAction);

}
