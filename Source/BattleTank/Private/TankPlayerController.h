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
	

private: 
	
	ATank* GetControlledTank() const;
	
};