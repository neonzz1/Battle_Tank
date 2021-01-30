// © Neonzz Games


#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend MoveForward: %f"), Throttle);

	//TODO clamp actual throttle vale so player can't overdrive

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}