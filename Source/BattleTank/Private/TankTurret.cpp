// © Neonzz Games


#include "TankTurret.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankTurret::UTankTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankTurret::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}