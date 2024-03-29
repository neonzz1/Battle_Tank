// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;
class UAudioComponent;

/**
 * Custom c++ for Tank movement
 */
UCLASS(	ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)	)
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	//Setup
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveRight(float Throw);

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	UAudioComponent* Idle;

protected:
	//Track Setup
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

	float StartTime = 1.0f;
	float NoiseMultiplier = 1.0f;
	float PitchMultiplier = 1.0f;

private:

	//Called from pathfinding logic
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bDriving();

	UPROPERTY(BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* EngineSound;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
