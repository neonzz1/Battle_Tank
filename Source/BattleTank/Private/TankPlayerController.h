// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" /* must me last */

//Forward Declorations
class ATank;

/**
 * 
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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

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

};