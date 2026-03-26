//
// Created by sarah on 24.03.26.
//

#include "../include/event_action.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"

void EventAction::BeginOfEventAction(const G4Event *anEvent) {

}

void EventAction::EndOfEventAction(const G4Event *anEvent) {
    G4TrajectoryContainer *trajectoryContainer = anEvent->GetTrajectoryContainer();
    std::size_t n_trajectories = 0;
    if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

    G4int eventID = anEvent->GetEventID();
    if (eventID < 100 || eventID % 100 == 0) {
        G4cout << ">>> Event: " << eventID << G4endl;
        if (trajectoryContainer) {
            G4cout << "   " << n_trajectories << " trajectories stored in this event." << G4endl;
        }
        G4VHitsCollection *hc = anEvent->GetHCofThisEvent()->GetHC(0);
        G4cout << "   " << hc->GetSize() << " hits stored in this event" << G4endl;
    }
}
