// © Neonzz Games


#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetName();

}