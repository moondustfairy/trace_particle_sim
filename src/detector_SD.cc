//
// Created by sarah on 24.03.26.
//

#include "detector_SD.hh"


#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"

DetectorSD::DetectorSD(const G4String &name, const G4String &hitsCollectionName) : G4VSensitiveDetector(name){
    collectionName.insert(hitsCollectionName);
}

void DetectorSD::Initialize(G4HCofThisEvent *hitCollection) {
    fHitsCollection = new DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitCollection->AddHitsCollection(hcID, fHitsCollection);

}

G4bool DetectorSD::ProcessHits(G4Step *step, G4TouchableHistory *history) {
    auto edep = step->GetTotalEnergyDeposit();
    DetectorHits *newHit = new DetectorHits();

    newHit->SetTrackID(step->GetTrack()->GetTrackID());
    newHit->SetEnergy(edep);
    newHit->SetPos(step->GetPostStepPoint()->GetPosition());

    auto hit = (*fHitsCollection)[0];
    auto hitTotal = (*fHitsCollection)[fHitsCollection->entries() - 1];
    hit->AddEdep(edep);

    fHitsCollection->insert(newHit);

    return true;
}

void DetectorSD::EndOfEvent(G4HCofThisEvent *hitCollection) {
    if (verboseLevel > 1) {
        std::size_t nofHits = fHitsCollection->entries();
        G4cout << G4endl << "--------------->Hits Collection_ in this event there are " << nofHits << " hits in the  " << G4endl;
        for (std::size_t i = 0; i < nofHits; i++)
            (*fHitsCollection)[i]->Print();
    }

}
