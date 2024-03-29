// © Neonzz Games

#include "TankMovementComponent.h"
#include "TankTracks.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Tank.h"

void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}


void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);

}

void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDriving() == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving!"));
	}
	else if (bDriving() == false)
	{
		bool bTestBool = true;
		UE_LOG(LogTemp, Warning, TEXT("Am I Driving? %b"), bTestBool);
	}

}

bool UTankMovementComponent::bDriving()
{
	float Movement = GetOwner()->GetActorForwardVector().GetSafeNormal().X;

	float Test = GetOwner()->GetVelocity().GetSafeNormal().X;

	float IdleFloat = 0.009f;

	if (FMath::IsNearlyEqual(Movement, Test, IdleFloat))
	{
		return true;
	}

	else 
	{
		return false;
	}
	
}

