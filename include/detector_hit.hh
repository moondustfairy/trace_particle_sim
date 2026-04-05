//
// Created by sarah on 24.03.26.
//

#ifndef TRACE_PARTICLE_SIM_TRACKERHITS_H
#define TRACE_PARTICLE_SIM_TRACKERHITS_H

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

#include "G4Threading.hh"
#include "G4ThreeVector.hh"
#include "G4VHit.hh"

class DetectorHit : public G4VHit {
public:
        DetectorHit() = default;
        DetectorHit(const DetectorHit&) = default;
        ~DetectorHit() override = default;

        DetectorHit& operator=(const DetectorHit&) = default;
        G4bool operator==(const DetectorHit&) const;

        inline void *operator new(size_t);
        inline void operator delete(void*);

        void Draw() override;
        void Print() override;

        void SetTrackID(G4int track) { fTrackID = track; };
        void SetEnergy(G4double e) { fEnergy = e; };
        void SetStepLength(G4double l) { fStepLength = l; };
        void SetMomentum(G4ThreeVector mom) { fMomentum = mom; };
        void SetPos(G4ThreeVector xyz) { fPos = xyz; };

        G4int GetTrackID() const { return fTrackID; };
        G4double GetEnergy() const { return fEnergy; };
        G4double GetStepLength() const { return fStepLength; };
        G4ThreeVector GetMomentum() const {return fMomentum; };
        G4ThreeVector GetPos() const { return fPos; };

private:
        G4int fTrackID = -1;
        G4double fEnergy = 0.;
        G4double fStepLength = 0.;
        G4ThreeVector fMomentum;
        G4ThreeVector fPos;
};

using DetectorHitCollection = G4THitsCollection<DetectorHit>;

extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

inline void *DetectorHit::operator new(size_t) {
        if (!DetectorHitAllocator) DetectorHitAllocator = new G4Allocator<DetectorHit>;
        return (void*)DetectorHitAllocator->MallocSingle();
}

inline void DetectorHit::operator delete(void *hit) {
        DetectorHitAllocator->FreeSingle((DetectorHit*)hit);
}

#endif //TRACE_PARTICLE_SIM_TRACKERHITS_H