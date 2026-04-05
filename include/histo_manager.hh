#ifndef HistoManager_h
#define HistoManager_h 1

#include "G4AnalysisManager.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
public:
    HistoManager();
    ~HistoManager() = default;

    void Book();
    void Save();

    void FillHisto(G4int id, G4double e, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);

    void FillNtuple(G4double EnergyTube, G4double EnergyCyl, G4double TrackLTube, G4double TrackLCyl);

    void PrintStatistic();

private:
    G4bool fFactoryOn = false;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
