// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTrack is used to set maximum driving force and apply forces
 */
UCLASS(	ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)	)
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//sets a throttlw between +1 and -1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float TrackMaxDrivingForce = 40000000.f; //40 ton tank 1g acceleration

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	void DriveTracks();

private:

	UTankTracks();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
