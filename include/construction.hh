#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4Color.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction 
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction() override;

	G4VPhysicalVolume *Construct() override;
	void ConstructSDandField() override;

private:
	G4LogicalVolume *fLogicDetectorTube = nullptr;
	G4LogicalVolume *fLogicBrainCylinder = nullptr;
	static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger;
};

#endif
