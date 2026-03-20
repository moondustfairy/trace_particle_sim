//
// Created by sarah on 18.03.26.
//

#include "run_action.hh"
#include "histo_manager.hh"

RunAction::RunAction() : G4UserRunAction(), fHistoManager(0)
{
    fHistoManager = new HistoManager();
}

RunAction::~RunAction()
{
    delete fHistoManager;
}

void RunAction::BeginRunAction(const G4Run *) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->OpenFile();
    }
}

void RunAction::EndRunAction(const G4Run *) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->Write();
        analysisManager->CloseFile();
    }
}
