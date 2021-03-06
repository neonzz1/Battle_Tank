// © Neonzz Games

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enums
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

//forward decloration
class UBarrel; 
class UTankTurret;
class AProjectile;

//Aiming and rotation of barrel and turret
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	EFiringStatus FireState = EFiringStatus::Reloading;


private:

	void MoveBarrelTowards(FVector AimDirection);

	void TurnTurretTowards(FVector AimDirection);

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UTankAimingComponent();

	double LastFireTime = 0;

	bool bIsBarrelMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "setup")
	int32 Ammo = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	FVector AimDirecton;

};
