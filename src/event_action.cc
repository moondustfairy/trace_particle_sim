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
#include "histo_manager.hh"
#include "run_action.hh"

EventAction::EventAction(RunAction *run, HistoManager *histo) : fRunAct(run), fHistoManager(histo) {}

DetectorHitCollection *EventAction::GetHitsCollection(G4int hcID, const G4Event *event) const {
    auto hitsCollection = static_cast<DetectorHitCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
    if (!hitsCollection) {
        G4ExceptionDescription ex;
        ex << "hitsCollection wit ID " << hcID << " not accessible";
        G4Exception("EventAction::GetHitsCollection()", "NewCode0001", FatalException, ex);
    }

    return hitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event *anEvent) {
    G4cout << "EventAction::BeginOfEventAction(event) : Event: " << anEvent->GetEventID() << "PDG code: " <<
        anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode()<<  G4endl;
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
        ex << "Warning: One or both hit collections are empty. Event ID: " << anEvent->GetEventID() << ", Particle: " << anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode() << ", Tube hits: " << tubeHC->entries() << ", Cylinder hits: " << cylinderHC->entries() << G4endl;
        G4Exception("EventAction::EndOfEventAction()", "NewCode0002", JustWarning, ex);
        return;
    }

    G4cout << "EventAction::EndOfEventAction(event) : " << anEvent->GetEventID() << ": Tube hits = " << tubeHC->entries()
           << ", Cylinder hits = " << cylinderHC->entries() << G4endl;

    auto tubeHit = (*tubeHC)[tubeHC->entries() - 1];
    auto cylinderHit = (*cylinderHC)[cylinderHC->entries() - 1];

    auto eventID = anEvent->GetEventID();
    auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    //if ((printModulo > 0) && (eventID % printModulo == 0)) {
        G4cout << " Primary Vertex Energy: " << std::setw(7) << G4BestUnit(anEvent->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy(), "Energy") << G4endl;
        G4cout << " Primary Vertex Mass: " << std::setw(9) << G4BestUnit(anEvent->GetPrimaryVertex()->GetPrimary()->GetMass(), "Energy") << G4endl;
        G4cout << " Primary Vertex Charge: " << std::setw(7) << G4BestUnit(anEvent->GetPrimaryVertex()->GetPrimary()->GetCharge(), "Electric charge") << G4endl;
        G4cout << G4endl;
        G4cout << " Tube: total deposited energy: " << std::setw(7) << G4BestUnit(tubeHit->GetEnergy(), "Energy") << G4endl;
        G4cout  << " step length: " << std::setw(10) << G4BestUnit(tubeHit->GetStepLength(), "Length") << G4endl;
        G4cout << " Cylinder: total deposited energy: " << std::setw(7) << G4BestUnit(cylinderHit->GetEnergy(), "Energy") << G4endl;
        G4cout  << " step length: " << std::setw(10) << G4BestUnit(cylinderHit->GetStepLength(), "Length") << G4endl;
        G4cout << " ------------------ End of Event: " << eventID << "----------------------------\n" << G4endl;
    //}

    fRunAct->FillPerEvent(tubeHit->GetEnergy(), cylinderHit->GetEnergy(), tubeHit->GetStepLength(), cylinderHit->GetStepLength());

    fHistoManager->FillHisto(0, tubeHit->GetEnergy());
    fHistoManager->FillHisto(1, cylinderHit->GetEnergy());
    fHistoManager->FillHisto(2, tubeHit->GetStepLength());
    fHistoManager->FillHisto(3, cylinderHit->GetStepLength());
    fHistoManager->FillHisto(4, anEvent->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy());

    fHistoManager->FillNtuple(tubeHit->GetEnergy(), cylinderHit->GetEnergy(), tubeHit->GetStepLength(), cylinderHit->GetStepLength());
}
