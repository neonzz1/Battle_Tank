// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" /* must me last */

//Forward Declorations
class UTankAimingComponent;

/**
 * Controlls Player Tanks
 */
UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	void AimTowardsCrosshair();

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private: 
	
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float LineTraceRange = 100000.f;

	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnPossesedTankDeath();

};