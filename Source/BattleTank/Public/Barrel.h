// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */
UCLASS(	ClassGroup=(Custom), meta=(BlueprintSpawnableComponent)	)
class BATTLETANK_API UBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed +1is max upwards speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40;
};
