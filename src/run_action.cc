//
// Created by sarah on 18.03.26.
//

#include "run_action.hh"

#include <G4HCtable.hh>
#include <G4UnitsTable.hh>

#include "detector_hit.hh"
#include "G4RunManager.hh"
#include "histo_manager.hh"
#include "G4AccumulableManager.hh"

#include "analysis.hh"

RunAction::RunAction(HistoManager *histo) : fHistoManager(histo) {
    G4RunManager::GetRunManager()->SetPrintProgress(10);


    // Register accumulable to the accumulable manager
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Register(fSumETube);
    accumulableManager->Register(fSumECyl);
    accumulableManager->Register(fSumLTube);
    accumulableManager->Register(fSumLCyl);

}

RunAction::~RunAction() {
}

void RunAction::BeginOfRunAction(const G4Run *run) {
    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

    // reset accumulables to their initial values
    G4AccumulableManager::Instance()->Reset();

    // histograms
    //
    fHistoManager->Book();
}

void RunAction::FillPerEvent(G4double ETube, G4double ECyl, G4double LTube, G4double LCyl) {
    // accumulate statistic
    //
   fSumETube += ETube;
   fSumECyl += ECyl;
   fSumLTube += LTube;
   fSumLCyl += LCyl;
}

void RunAction::EndOfRunAction(const G4Run *run) {

    G4AccumulableManager::Instance()->Merge();

    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) {
        // close open files
        fHistoManager->Save();
        return;
    }
    if (run->GetHCtable()->GetHCname(0) == "TubeHitsCollection")
        G4cout << "Number of hits in tube: " << run->GetHCtable()->GetCollectionID("TubeHitsCollection") << G4endl; {
    }
    if (run->GetHCtable()->GetHCname(1) == "CylinderHitsCollection")
        G4cout << "Number of hits in cylinder: " << run->GetHCtable()->GetCollectionID("CylinderHitsCollection") << G4endl; {
        }

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->IsActive()) {
        analysisManager->Write();
        analysisManager->CloseFile();
    }
    fHistoManager->Save();
}
