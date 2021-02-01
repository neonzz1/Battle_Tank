// © Neonzz Games

#include "TankAimingComponent.h"
#include "Barrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#define OUT
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	auto BarrelLocation = Barrel->GetComponentLocation();
	auto InitialElevation = Barrel->GetComponentRotation();
	auto InitialTurretRotation = Turret->GetComponentRotation();

	OUT FVector LaunchVelocity;

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHasAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		auto Time = GetWorld()->GetTimeSeconds();

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);

}



void UTankAimingComponent::TurnTurretTowards(FVector AimDirection)
{

}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool bisReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (bisReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

		//Spawn Projectile at socket on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}