//
// Created by sarah on 24.03.26.
//

#ifndef TRACE_PARTICLE_SIM_EVENT_ACTION_HH
#define TRACE_PARTICLE_SIM_EVENT_ACTION_HH

#include "detector_hits.hh"
#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"

class G4Event;

class EventAction : public G4UserEventAction {
public:
        EventAction() = default;
        ~EventAction() override = default;

        void BeginOfEventAction(const G4Event *anEvent) override;
        void EndOfEventAction(const G4Event *anEvent) override;

private:
        G4double fDepositedEnergy;
        G4int fTubeHCID = -1;
        G4int fCylinderHCID = -1;

        DetectorHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
};


#endif //TRACE_PARTICLE_SIM_EVENT_ACTION_HH