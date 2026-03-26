//
// Created by sarah on 24.03.26.
//

#ifndef TRACE_PARTICLE_SIM_TRACKERSD_H
#define TRACE_PARTICLE_SIM_TRACKERSD_H

#include "detector_hits.hh"

#include "G4VSensitiveDetector.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;

class DetectorSD : public G4VSensitiveDetector {
    public:
        DetectorSD(const G4String& name, const G4String& hitsCollectionName);
        ~DetectorSD() override = default;

        void Initialize(G4HCofThisEvent *hitCollection) override;
        G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
        void EndOfEvent(G4HCofThisEvent *hitCollection) override;

    private:
        DetectorHitsCollection *fHitsCollection = nullptr;
};


#endif //TRACE_PARTICLE_SIM_TRACKERSD_H