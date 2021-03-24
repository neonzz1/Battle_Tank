// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 * Custom c++ for Tank movement
 */
UCLASS(	ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)	)
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet, UAudioComponent* AudioComponentIdleToSet, UAudioComponent* AudioComponentMovingToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveRight(float Throw);

	bool EngineRevSound = false;

	bool EngineIdleSound = true;

	void IdleSound();

protected:

	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

private:

	//Called from pathfinding logic
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UPROPERTY()
	UAudioComponent* AudioComponentIdle = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponentEngine = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
