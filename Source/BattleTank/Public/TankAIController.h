// © Neonzz Games

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()


public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	ATank* GetControlledTank();

	ATank* GetPlayerTank();

};
