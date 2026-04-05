#include "../include/construction.hh"

#include <G4ThreadLocalSingleton.hh>

#include "detector_SD.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4AutoDelete.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();

	G4VisAttributes shellColour(G4Colour(0., 1., 0., 0.7));
	G4VisAttributes worldColour(G4Colour(0, 0, 1.));
	G4VisAttributes detectorColour(G4Colour::Red());
	G4VisAttributes brainCylinderColour(G4Colour(0.5, 0., 1.0, 0.3));

	// --------------------------------------- DEFINE MATERIALS -------------------------------------------------------

	G4Material *elAl =  nist->FindOrBuildMaterial("G4_Al");
	G4Material *elMg =  nist->FindOrBuildMaterial("G4_Mg");
	G4Material *elSi =  nist->FindOrBuildMaterial("G4_Si");
	G4Material *elFe =  nist->FindOrBuildMaterial("G4_Fe");
	G4Material *elCu =  nist->FindOrBuildMaterial("G4_Cu");
	G4Material *elCr =  nist->FindOrBuildMaterial("G4_Cr");
	G4Material *elMn =  nist->FindOrBuildMaterial("G4_Mn");
	G4Material *elZn =  nist->FindOrBuildMaterial("G4_Zn");
	G4Material *elTi =  nist->FindOrBuildMaterial("G4_Ti");


	// aerospace-grade 6061 aluminum alloy for shell (weight fractions, upper limit): Al 96%, Mg 1.2%, Si 0.8%, Fe 0.7%, Cu 0.4%, Cr 0.35%, Mn 0.15%, Zn 0.25%, Ti 0.15%
	// source: https://www.weltstahl.com/6061-aluminium/
	G4double alloyDensity = 2.7*g/cm3;
	G4Material *alAlloyMat = new G4Material("aluminumAlloy", alloyDensity, 9);
	alAlloyMat->AddMaterial(elAl, 96.*perCent);
	alAlloyMat->AddMaterial(elMg, 1.2*perCent);
	alAlloyMat->AddMaterial(elSi, 0.8*perCent);
	alAlloyMat->AddMaterial(elFe, 0.7*perCent);
	alAlloyMat->AddMaterial(elCu, 0.4*perCent);
	alAlloyMat->AddMaterial(elCr, 0.35*perCent);
	alAlloyMat->AddMaterial(elMn, 0.15*perCent);
	alAlloyMat->AddMaterial(elZn, 0.25*perCent);
	alAlloyMat->AddMaterial(elTi, 0.15*perCent);

	// low-density air at 520km altitude on Earth
	G4double airDensity = 1.e-12*kg/m3;
	G4Material *worldMat = nist->BuildMaterialWithNewDensity("lowDensityAir", "G4_AIR", airDensity);

	// vacuum for satellite filling
	G4Material *vacuumMat = nist->FindOrBuildMaterial("G4_Galactic");

	G4Material *boneMat = nist->FindOrBuildMaterial("G4_B-100_BONE");
	G4Material *brainMat = nist->FindOrBuildMaterial("G4_BRAIN_ICRP");

	// --------------------------------------- DEFINE VOLUMES ---------------------------------------------------------

	G4Sphere *solidWorld = new G4Sphere("solidWorld", 0.*m, 0.2*m, 0, CLHEP::twopi, 0, CLHEP::pi);

	// hollow TRACE structure, 2U CubeSat: half length in x and y 5cm, length in z 10cm, thickness 1mm
	G4Box *traceOuterShell = new G4Box("traceOuterShell", 5.*cm, 5.*cm, 10.*cm);
	G4Box *traceInnerShell = new G4Box("traceInnerShell", 4.9*cm, 4.9*cm, 9.9*cm);
	G4SubtractionSolid	*traceShell = new G4SubtractionSolid("traceShell", traceOuterShell, traceInnerShell);

	// Copper detector tube: diameter 12mm, length 20mm, thickness 0.5mm
	G4Tubs *boneTube = new G4Tubs("detectorTube", .55*cm, .6*cm, 1.*cm, 0, CLHEP::twopi);
	G4Tubs *boneAndBrainCylinder = new G4Tubs("boneAndBrainCylinder", 0.*cm, .6*cm, 1.*cm, 0, CLHEP::twopi);
	G4SubtractionSolid *brainCylinder = new G4SubtractionSolid("boneCylinder", boneAndBrainCylinder, boneTube);
	G4RotationMatrix *tubeRotation = new G4RotationMatrix();
	tubeRotation->rotateY(90.*degree);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4LogicalVolume *logicTraceShell = new G4LogicalVolume(traceShell, alAlloyMat, "logicTraceShell");
	//G4LogicalVolume *logicTraceVacuum = new G4LogicalVolume(traceInnerShell, vacuumMat, "logicTraceVacuum");
	G4LogicalVolume *logicBoneTube = new G4LogicalVolume(boneTube, boneMat, "logicBoneTube");
	G4LogicalVolume *logicBrainCylinder = new G4LogicalVolume(brainCylinder, brainMat, "logicBrainCylinder");

	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	G4VPhysicalVolume *physTraceShell = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTraceShell, "physTraceShell", logicWorld, false, 0, true);
	//G4VPhysicalVolume *physTraceVacuum = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTraceVacuum, "physTraceVacuum", logicTraceShell, false, 0, true);
	G4VPhysicalVolume *physBoneTube = new G4PVPlacement(tubeRotation, G4ThreeVector(0., 0., 0.), logicBoneTube, "physDetectorTube", logicWorld, false, 0, true);
	G4VPhysicalVolume *physBrainCylinder = new G4PVPlacement(tubeRotation, G4ThreeVector(0., 0., 0.), logicBrainCylinder, "physBrainCylinder", logicWorld, false, 0, true);

	fLogicDetectorTube = logicBoneTube;
	fLogicBrainCylinder = logicBrainCylinder;

	G4VisAttributes *logicWorldVisAtt = new G4VisAttributes(worldColour);
	//logicWorldVisAtt->SetForceSolid(true);
	logicWorld->SetVisAttributes(logicWorldVisAtt);

	G4VisAttributes *logicShellVisAtt = new G4VisAttributes(shellColour);
	//logicShellVisAtt->SetForceSolid(true);
	logicTraceShell->SetVisAttributes(logicShellVisAtt);

	G4VisAttributes *logicDetectorTubeVisAtt = new G4VisAttributes(detectorColour);
	logicDetectorTubeVisAtt->SetForceSolid(true);
	logicBoneTube->SetVisAttributes(logicDetectorTubeVisAtt);

	G4VisAttributes *logicBrainCylinderVisAtt = new G4VisAttributes(brainCylinderColour);
	logicBrainCylinderVisAtt->SetForceSolid(true);
	logicBrainCylinder->SetVisAttributes(logicBrainCylinderVisAtt);

	G4AutoDelete::Register(logicWorldVisAtt);
	G4AutoDelete::Register(logicDetectorTubeVisAtt);
	G4AutoDelete::Register(logicBrainCylinderVisAtt);
	G4AutoDelete::Register(tubeRotation);
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
	G4String tubeSDName = "/tubeSD";
	G4String cylinderSDName = "/cylinderSD";
	auto tubeSD = new DetectorSD(tubeSDName, "TubeHitsCollection");
	auto cylinderSD = new DetectorSD(cylinderSDName, "CylinderHitsCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(tubeSD);
	G4SDManager::GetSDMpointer()->AddNewDetector(cylinderSD);
	if (fLogicDetectorTube) {
		fLogicDetectorTube->SetSensitiveDetector(tubeSD);
	}
	if (fLogicBrainCylinder) {
		fLogicBrainCylinder->SetSensitiveDetector(cylinderSD);
	}

	//G4ThreeVector earthMagField = G4ThreeVector();
	//fMagFieldMessenger = new G4GlobalMagFieldMessenger(earthMagField);
	//fMagFieldMessenger->SetVerboseLevel(1);
	//G4UniformMagField *earthMagField = new G4UniformMagField(G4ThreeVector(.5e-4*tesla, 0., 0.));
	//G4FieldManager *globalFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	//globalFieldMgr->SetDetectorField(earthMagField);

	//G4AutoDelete::Register(fMagFieldMessenger);

}

