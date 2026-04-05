//
// Created by sarah on 24.03.26.
//

#include "../include/detector_hit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator = nullptr;

G4bool DetectorHit::operator==(const DetectorHit &right) const {
    return (this==&right) ? true : false;
}

void DetectorHit::Draw() {
    /*
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager) {
        G4Circle circle(fPos);
        circle.SetWorldDiameter(.5*CLHEP::mm);
        circle.SetFillStyle(G4Circle::filled);

        G4Colour colour(0.5, 0, 1.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);

        pVVisManager->Draw(circle);

    }
    */
}

void DetectorHit::Print() {
    G4cout << " trackID: " << fTrackID << "Edep: " << std::setw(7)
    << G4BestUnit(fEnergy, "Energy") << " Position: " << std::setw(7)
    << G4BestUnit(fPos, "Length") << G4endl;
}
