// © Neonzz Games

#pragma once

#include "tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" /* must me last */

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

private: 
	
	ATank* GetControlledTank() const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.f;

};