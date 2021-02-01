// © Neonzz Games


#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Claculate Slippage
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Required Correction Acceleration 
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Apply Forces
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);

}

void UTankTracks::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend MoveForward: %f"), Throttle);

	Throttle = FMath::Clamp<float>(Throttle, -1.5, +1.5); // no overdrive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}