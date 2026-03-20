//
// Created by sarah on 18.03.26.
//

#ifndef TRACE_PARTICLE_SIM_RUN_ACTION_H
#define TRACE_PARTICLE_SIM_RUN_ACTION_H

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"

class G4Run;
class HistoManager;

class RunAction : public G4UserRunAction
{
    public:
        RunAction();
        ~RunAction();

        virtual void BeginRunAction(const G4Run*);
        virtual void EndRunAction(const G4Run*);

    private:
        HistoManager* fHistoManager;
};

#endif //TRACE_PARTICLE_SIM_RUN_ACTION_H