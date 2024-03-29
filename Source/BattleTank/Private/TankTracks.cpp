// © Neonzz Games


#include "TankTracks.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, +1); // no overdrive
	DriveTracks(CurrentThrottle);
}

void UTankTracks::DriveTracks(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 12; // Twelve wheels
	TankRoot->AddForce(CorrectionForce);
}

TArray<class ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;

	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		
		if (!SprungWheel) { continue; }
		ResultArray.Add(SprungWheel);
	}
	
	return ResultArray;
}
