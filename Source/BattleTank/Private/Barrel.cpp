// © Neonzz Games


#include "Barrel.h"

void UBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	
	SetRelativeRotation(FRotator(Elevation, 0, 0));

}