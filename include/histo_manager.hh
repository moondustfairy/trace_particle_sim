//
// Created by sarah on 18.03.26.
//

#ifndef TRACE_PARTICLE_SIM_HISTO_MANAGER_H
#define TRACE_PARTICLE_SIM_HISTO_MANAGER_H

#include "G4AnalysisManager.hh"
#include "globals.hh"

class HistoManager
{
    public:
        HistoManager();
        ~HistoManager();

    private:
        void Book();
        G4String fFileName;
};


#endif //TRACE_PARTICLE_SIM_HISTO_MANAGER_H