// © Neonzz Games


#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Aim solution Found %f"), *Name, Throttle);
}