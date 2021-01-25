// © Neonzz Games

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//forward decloration
class UBarrel; 
class UTankTurret;

//Aiming and rotation of barrel and turret
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UBarrel* BarrelToSet);
	//TODO set turret referance
	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetTurretReference(UTankTurret* TurretToSet);

private:

	UBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	void TurnTurretTowards(FVector AimDirection);
		
};
