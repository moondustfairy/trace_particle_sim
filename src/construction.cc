#include "../include/construction.hh"
#include "../include/CADMesh.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();


	// aerospace-grade 6061 aluminum alloy for shell (weight fractions): Al 95.85%, Mg 0.8%, Si 0.4%, Cu 0.15%, Cr 0.04%
	G4double alloyDensity = 2.7*g/cm3;
	G4int ncomponents;
	G4Material *elAl =  nist->FindOrBuildMaterial("G4_Al");
	G4Material *elMg =  nist->FindOrBuildMaterial("G4_Mg");
	G4Material *elSi =  nist->FindOrBuildMaterial("G4_Si");
	G4Material *elCu =  nist->FindOrBuildMaterial("G4_Cu");
	G4Material *elCr =  nist->FindOrBuildMaterial("G4_Cr");
	G4Material *alAlloy = new G4Material("aluminumAlloy", alloyDensity, ncomponents=5);
	alAlloy->AddMaterial(elAl, 95.85*perCent);
	alAlloy->AddMaterial(elMg, 0.8*perCent);
	alAlloy->AddMaterial(elSi, 0.4*perCent);
	alAlloy->AddMaterial(elCu, 0.15*perCent);
	alAlloy->AddMaterial(elCr, 0.04*perCent);

	// low-density air at 520km altitude on Earth

	G4double airDensity = 1.e-12*kg/m3;
	G4Material *worldMat = nist->BuildMaterialWithNewDensity("lowDensityAir", "G4_AIR", airDensity);

	G4Box *solidWorld = new G4Box("solidWorld", 1.*m, 1.*m, 1.*m);

	G4Box *traceOuterShell = new G4Box("traceOuterShell", 5.*cm, 5.*cm, 10.*cm);
	G4Box *traceInnerShell = new G4Box("traceInnerShell", 4.95*cm, 4.95*cm, 9.95*cm);

	G4SubtractionSolid	*traceShell = new G4SubtractionSolid("traceOuterShell-traceInnerShell", traceOuterShell, traceInnerShell);

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4LogicalVolume *logicTraceShell = new G4LogicalVolume(traceShell, alAlloy, "logicTraceShell");
	
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	G4VPhysicalVolume *physTraceShell = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTraceShell, "physTraceShell", logicWorld, false, 0, true);
	return physWorld;
}
