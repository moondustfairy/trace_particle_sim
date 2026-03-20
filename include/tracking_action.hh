//
// Created by sarah on 18.03.26.
//

#ifndef TRACE_PARTICLE_SIM_TRACKING_ACTION_H
#define TRACE_PARTICLE_SIM_TRACKING_ACTION_H

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "globals.hh"

class G4Track;

class TrackingAction : public G4UserTrackingAction
{
	public:
		TrackingAction();
		~TrackingAction() {};

	virtual void PreUserTrackingAction(const G4Track*);
};

#endif //TRACE_PARTICLE_SIM_TRACKING_ACTION_H