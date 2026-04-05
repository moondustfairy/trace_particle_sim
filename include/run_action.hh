//
// Created by sarah on 18.03.26.
//

#ifndef TRACE_PARTICLE_SIM_RUN_ACTION_H
#define TRACE_PARTICLE_SIM_RUN_ACTION_H

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Accumulable.hh"
#include "G4Run.hh"
#include "globals.hh"

class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
    public:
        RunAction(HistoManager*);
        ~RunAction() override;

        void BeginOfRunAction(const G4Run*) override;
        void EndOfRunAction(const G4Run*) override;

        void FillPerEvent(G4double, G4double, G4double, G4double);

    private:
        HistoManager* fHistoManager = nullptr;

        G4Accumulable<G4double> fSumETube = 0.;
        G4Accumulable<G4double> fSumECyl = 0.;

        G4Accumulable<G4double> fSumLTube = 0.;
        G4Accumulable<G4double> fSumLCyl = 0.;
};

#endif //TRACE_PARTICLE_SIM_RUN_ACTION_H