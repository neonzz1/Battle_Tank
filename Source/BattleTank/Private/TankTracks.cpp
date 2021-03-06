// © Neonzz Games


#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankTracks::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTracks();
	ApplySidewaysForce();
	CurrentThrottle = 0;

}

void UTankTracks::ApplySidewaysForce()
{
	//Claculate Slippage
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Required Correction Acceleration 
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Apply Forces
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend MoveForward: %f"), Throttle);

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1); // no overdrive

}

void UTankTracks::DriveTracks()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//UE_LOG(LogTemp, Warning, TEXT("Intend DriveTrack: %f"), CurrentThrottle);
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}