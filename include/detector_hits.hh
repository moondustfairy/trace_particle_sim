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

class DetectorHits : public G4VHit {
public:
        DetectorHits() = default;
        DetectorHits(const DetectorHits&) = default;
        ~DetectorHits() override = default;

        DetectorHits& operator=(const DetectorHits&) = default;
        G4bool operator==(const DetectorHits&) const;

        inline void *operator new(size_t);
        inline void operator delete(void*);

        void Draw() override;
        void Print() override;

        void SetTrackID(G4int track) { fTrackID = track; };
        void SetEnergy(G4double e) { fEnergy = e; };
        void SetMomentum(G4ThreeVector mom) { fMomentum = mom; };
        void SetPos(G4ThreeVector xyz) { fPos = xyz; };

        G4int GetTrackID() const { return fTrackID; };
        G4double GetEnergy() const { return fEnergy; };
        G4ThreeVector GetMomentum() const {return fMomentum; };
        G4ThreeVector GetPos() const { return fPos; };

        void AddEdep(G4double edep);

private:
        G4int fTrackID = -1;
        G4double fEnergy = 0.;
        G4ThreeVector fMomentum;
        G4ThreeVector fPos;
};

using DetectorHitsCollection = G4THitsCollection<DetectorHits>;

extern G4ThreadLocal G4Allocator<DetectorHits>* DetectorHitAllocator;

inline void *DetectorHits::operator new(size_t) {
        if (!DetectorHitAllocator) DetectorHitAllocator = new G4Allocator<DetectorHits>;
        return (void*)DetectorHitAllocator->MallocSingle();
}

inline void DetectorHits::operator delete(void *hit) {
        DetectorHitAllocator->FreeSingle((DetectorHits*)hit);
}

inline void DetectorHits::AddEdep(G4double edep) {
        fEnergy += edep;
}

#endif //TRACE_PARTICLE_SIM_TRACKERHITS_H