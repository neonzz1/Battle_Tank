// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
class ATank;

/**
 * Controls AI tanks
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UPROPERTY(EditAnywhere, Category ="Setup")
	float AcceptanceRadius = 7000.f;

	void FireTimerExpired();

private:

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossesedTankDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireTime = 2.0f;
	
	ATank* PlayerTank;

	ATank* ControlledTank;

	UTankAimingComponent* AimingComponent;

	FTimerHandle FireTimeHandle;

	UPROPERTY()
	TArray<AActor*> FoundActors;

};
