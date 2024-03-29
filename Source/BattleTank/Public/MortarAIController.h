// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MortarAIController.generated.h"

class UTankAimingComponent;
class ATank;
class AMortar;

/**
 * Controls All AutoMortars
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()


public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	float ReturnDistanceToPlayer();

	void CheckPlayerInRange();

private:

	virtual void SetPawn(APawn* InPawn) override;

	ATank* PlayerTank;

	AMortar* ControlledMortar;
	
	UTankAimingComponent* AimingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 20000.0f; //Find Sensable default
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireTime = 2.0f;

	FTimerHandle FireTimeHandle;
	
};
