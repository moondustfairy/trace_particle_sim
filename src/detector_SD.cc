//
// Created by sarah on 24.03.26.
//

#include "detector_SD.hh"

#include <G4AutoDelete.hh>


#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"

DetectorSD::DetectorSD(const G4String &name, const G4String &hitsCollectionName) : G4VSensitiveDetector(name){
    G4cout << "Constructing DetectorSD with name: " << name << " and hits collection name: " << hitsCollectionName << G4endl;
    collectionName.insert(hitsCollectionName);
    fCollectionID = -1;
}

void DetectorSD::Initialize(G4HCofThisEvent *eventHitCollection) {
    G4cout << "DetectorSD::Initialize() : Initializing hit  collection for " << SensitiveDetectorName << G4endl;
    fHitsCollection = new DetectorHitCollection(SensitiveDetectorName, collectionName[0]);

    if (fCollectionID < 0) {
        fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
    eventHitCollection->AddHitsCollection(fCollectionID, fHitsCollection);
}

G4bool DetectorSD::ProcessHits(G4Step *step, G4TouchableHistory *history) {
    G4cout << "DetectorSD::ProcessHits() : Particle in " << SensitiveDetectorName << " at position "
           << step->GetPostStepPoint()->GetPosition() << " with energy deposit "
           << step->GetTotalEnergyDeposit() << G4endl;

    auto edep = step->GetTotalEnergyDeposit();
    if (edep == 0.) return false;

    DetectorHit *newHit = new DetectorHit();
    G4AutoDelete::Register(newHit);
    newHit->SetTrackID(step->GetTrack()->GetTrackID());
    newHit->SetEnergy(edep);
    newHit->SetStepLength(step->GetStepLength());
    newHit->SetMomentum(step->GetTrack()->GetMomentum());
    newHit->SetPos(step->GetPostStepPoint()->GetPosition());
    fHitsCollection->insert(newHit);

    fTotalEnergyDeposit += edep;

    /*if (fHitsCollection->entries() == 0) {
        auto *newHit = new DetectorHits();
        G4AutoDelete::Register(newHit);
        newHit->SetTrackID(step->GetTrack()->GetTrackID());
        newHit->SetEnergy(edep);
        newHit->SetPos(step->GetPostStepPoint()->GetPosition());
        fHitsCollection->insert(newHit);
    } else {
        auto hit = (*fHitsCollection)[0];
        auto hitTotal = (*fHitsCollection)[fHitsCollection->entries() - 1];
        hit->AddEdep(edep);
        hitTotal->AddEdep(edep);
        hitTotal->AddEdep(edep);
    */
   // }
    return true;
}

void DetectorSD::EndOfEvent(G4HCofThisEvent *eventHitCollection) {

    if (verboseLevel > 1) {
        std::size_t nofHits = fHitsCollection->entries();
        G4cout << G4endl << "DetectorSD::EndOfEvent(HCofEvent) : In this event are " << nofHits << " hits in the  Hits Collection of " <<
        eventHitCollection->GetHC(0)->GetSDname() <<  G4endl;
        for (std::size_t i = 0; i < nofHits; i++)
            (*fHitsCollection)[i]->Print();
    }

}
