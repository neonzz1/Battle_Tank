// © Neonzz Games

#include "TankMovementComponent.h"
#include "TankTracks.h"
#include "Components/AudioComponent.h"


void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet, UAudioComponent* AudioComponentIdleToSet, UAudioComponent* AudioComponentMovingToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	AudioComponentIdle = AudioComponentIdleToSet;
	AudioComponentEngine = AudioComponentMovingToSet;

	IdleSound();
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	EngineIdleSound = false;

	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendMoveRight(float Throw)
{
	EngineIdleSound = false;

	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IdleSound()
{
	if (!EngineRevSound)
	{
		AudioComponentEngine->SetPaused(true);
		
		AudioComponentIdle->SetPaused(false);
		AudioComponentIdle->Play();
	}
}


void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);
}

void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{

}
