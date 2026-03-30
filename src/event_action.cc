//
// Created by sarah on 24.03.26.
//

#include "../include/event_action.hh"

#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4UnitsTable.hh>

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"

DetectorHitsCollection *EventAction::GetHitsCollection(G4int hcID, const G4Event *event) const {
    auto hitsCollection = static_cast<DetectorHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
    if (!hitsCollection) {
        G4ExceptionDescription ex;
        ex << "hitsCollection wit ID " << hcID << " not accessible";
        G4Exception("EventAction::GetHitsCollection()", "NewCode0001", FatalException, ex);
    }

    return hitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event *anEvent) {

}

void EventAction::EndOfEventAction(const G4Event *anEvent) {


    if (fCylinderHCID == -1) {
        fTubeHCID = G4SDManager::GetSDMpointer()->GetCollectionID("TubeHitsCollection");
        fCylinderHCID = G4SDManager::GetSDMpointer()->GetCollectionID("CylinderHitsCollection");
    }

    auto tubeHC = GetHitsCollection(fTubeHCID, anEvent);
    auto cylinderHC = GetHitsCollection(fCylinderHCID, anEvent);

    if (tubeHC->entries() == 0 || cylinderHC->entries() == 0) {
        G4ExceptionDescription ex;
        ex << "Warning: One or both hit collections are empty. Tube hits: " << tubeHC->entries() << ", Cylinder hits: " << cylinderHC->entries() << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "NewCode0002", JustWarning, ex);
        return;
    }

    G4cout << "Event " << anEvent->GetEventID() << ": Tube hits = " << tubeHC->entries()
           << ", Cylinder hits = " << cylinderHC->entries() << G4endl;

    auto tubeHit = (*tubeHC)[tubeHC->entries() - 1];
    auto cylinderHit = (*cylinderHC)[cylinderHC->entries() - 1];

    auto eventID = anEvent->GetEventID();
    auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ((printModulo > 0) && (eventID % printModulo == 0)) {
        G4cout << " Tube: total deposited energy: " << std::setw(7) << G4BestUnit(tubeHit->GetEnergy(), "Energy") << G4endl;
        G4cout  << " momentum: " << std::setw(7) << G4BestUnit(tubeHit->GetMomentum(), "Energy") << G4endl;
        G4cout << " Cylinder: total deposited energy: " << std::setw(7) << G4BestUnit(cylinderHit->GetEnergy(), "Energy") << G4endl;
        G4cout  << " momentum: " << std::setw(7) << G4BestUnit(cylinderHit->GetMomentum(), "Energy") << G4endl;
        G4cout << " ------------------ End of Event: " << eventID << "\n" << G4endl;
    }

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0, tubeHit->GetEnergy());
    analysisManager->FillH1(1, cylinderHit->GetEnergy());
    analysisManager->FillH1(2, tubeHit->GetMomentum().mag());
    analysisManager->FillH1(3, cylinderHit->GetMomentum().mag());
}
