//
// Created by sarah on 18.03.26.
//

#include "run_action.hh"

#include "G4RunManager.hh"

RunAction::RunAction() : G4UserRunAction() {
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // create analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    analysisManager->SetVerboseLevel(1);
    analysisManager->CreateH1("DepE","Deposited Energy in bone", 200,0., 500*CLHEP::MeV);
}

RunAction::~RunAction() {
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginRunAction(const G4Run *) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        G4String fileName = "data";
        analysisManager->OpenFile(fileName);
    }
}

void RunAction::EndRunAction(const G4Run *) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->Write();
        analysisManager->CloseFile();
    }
}
