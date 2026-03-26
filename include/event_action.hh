//
// Created by sarah on 24.03.26.
//

#ifndef TRACE_PARTICLE_SIM_EVENT_ACTION_HH
#define TRACE_PARTICLE_SIM_EVENT_ACTION_HH

#include "G4UserEventAction.hh"

class G4Event;

class EventAction : public G4UserEventAction {
public:
        EventAction() = default;
        ~EventAction() override = default;

        void BeginOfEventAction(const G4Event *anEvent) override;
        void EndOfEventAction(const G4Event *anEvent) override;
};


#endif //TRACE_PARTICLE_SIM_EVENT_ACTION_HH