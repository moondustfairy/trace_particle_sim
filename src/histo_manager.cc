// From Geant4 example AnaEx01


#include "histo_manager.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
{
  // Create or get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  // the default file type can be overriden in run macro
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if (!fFactoryOn) {
    //
    analysisManager->SetVerboseLevel(1);
    // Only merge in MT mode to avoid warning when running in Sequential mode
#ifdef G4MULTITHREADED
    analysisManager->SetNtupleMerging(true);
#endif

    // Create directories
    analysisManager->SetHistoDirectoryName("histo");
    analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(1);
  }

  // Open an output file
  //
  G4bool fileOpen = analysisManager->OpenFile("histo_gcr");
  if (!fileOpen) {
    G4cerr << "\n---> HistoManager::Book(): cannot open " << analysisManager->GetFileName()
           << G4endl;
    return;
  }

  if (!fFactoryOn) {
    // Create histograms.
    // Histogram ids are generated automatically starting from 0.
    // The start value can be changed by:
    // analysisManager->SetFirstHistoId(1);

    // id = 0
    analysisManager->CreateH1("ETube", "Edep in tube (MeV)", 100, 0., 200 * MeV);
    // id = 1
    analysisManager->CreateH1("ECylinder", "Edep in cylinder (MeV)", 100, 0., 200 * MeV);
    // id = 2
    analysisManager->CreateH1("LTube", "trackL in tube (mm)", 100, 0., 1 * m);
    // id = 3
    analysisManager->CreateH1("LCylinder", "trackL in cylinder (mm)", 100, 0., 50 * cm);
    // id = 4
    analysisManager->CreateH1("Energy_particles", "Energy of all particles (MeV)", 100, 0., 500 * MeV);

    // Create ntuples.
    // Ntuples ids are generated automatically starting from 0.
    // The start value can be changed by:
    // analysisManager->SetFirstMtupleId(1);

    // Create 1st ntuple (id = 0)
    analysisManager->CreateNtuple("Ntuple1", "Edep and trackL");
    analysisManager->CreateNtupleIColumn("EventID");  // column Id = 0
    analysisManager->CreateNtupleIColumn("PDGcode");  // column Id = 1
    analysisManager->CreateNtupleDColumn("ETube");  // column Id = 2
    analysisManager->CreateNtupleDColumn("ECylinder");  // column Id = 3
    analysisManager->CreateNtupleDColumn("LTube");  // column Id = 4
    analysisManager->CreateNtupleDColumn("LCylinder");  // column Id = 5
    analysisManager->FinishNtuple();

    fFactoryOn = true;
  }

  G4cout << "\n----> Output file is open in " << analysisManager->GetFileName() << "."
         << analysisManager->GetFileType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{
  if (!fFactoryOn) {
    return;
  }

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(ih, xbin, weight);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Normalize(G4int ih, G4double fac)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  auto h1 = analysisManager->GetH1(ih);
  if (h1 != nullptr) {
    h1->scale(fac);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple(G4int eventID, G4int particle_index, G4double eTube, G4double eCylinder, G4double trackTube,
                              G4double trackCylinder)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(0, 0, eventID);
  analysisManager->FillNtupleIColumn(0, 1, particle_index);
  analysisManager->FillNtupleDColumn(0, 2, eTube);
  analysisManager->FillNtupleDColumn(0, 3, eCylinder);
  analysisManager->FillNtupleDColumn(0, 4, trackTube);
  analysisManager->FillNtupleDColumn(0, 5, trackCylinder);
  analysisManager->AddNtupleRow(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::PrintStatistic()
{
  if (!fFactoryOn) {
    return;
  }

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4cout << "\n ----> print histograms statistic \n" << G4endl;
  for (G4int i = 0; i < analysisManager->GetNofH1s(); ++i) {
    G4String name = analysisManager->GetH1Name(i);
    auto h1 = analysisManager->GetH1(i);

    G4String unitCategory;
    if (name[0U] == 'E') {
      unitCategory = "Energy";
    }
    if (name[0U] == 'L') {
      unitCategory = "Length";
    }
    // we use an explicit unsigned int type for operator [] argument
    // to avoid problems with windows compiler

    G4cout << name << ": mean = " << G4BestUnit(h1->mean(), unitCategory)
           << " rms = " << G4BestUnit(h1->rms(), unitCategory) << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......