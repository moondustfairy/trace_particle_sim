#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "Shielding.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv){

	// detect interaction mode if no arguments and define UI session
	G4UIExecutive *ui = nullptr;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv, "OGL");
	}

	G4int precision = 4;
	G4SteppingVerbose::UseBestUnit(precision);

	G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new MyDetectorConstruction());
	auto physics_list = new Shielding;
	runManager->SetUserInitialization(physics_list);
	//runManager->SetUserInitialization(new MyPhysicsList);
	runManager->SetUserInitialization(new MyActionInitialization());
	runManager->Initialize();
	
	G4VisManager *visManager = new G4VisExecutive(argc, argv);
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	 if (!ui) {
		// batch mode
	 	G4String command = "/control/execute ";
	 	G4String fileName = argv[1];
	 	UImanager->ApplyCommand(command + fileName);
	 } else {
		 // interactive mode
	 	UImanager->ApplyCommand("/control/execute init_vis.mac");
	 	ui->SessionStart();
	 	delete ui;
	 }

	delete visManager;
	delete runManager;
	return 0;
}
