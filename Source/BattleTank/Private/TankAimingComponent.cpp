// © Neonzz Games

#include "Barrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

#define OUT
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should this Tick?

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
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

		UE_LOG(LogTemp, Warning, TEXT("%f Aim solution Found"), Time);

		MoveBarrelTowards(AimDirection);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f No aim solution"), Time);
	}

}

void UTankAimingComponent::SetBarrelReference(UBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
}



void UTankAimingComponent::TurnTurretTowards(FVector AimDirection)
{
	auto TurretRotation = Turret->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotation;

	
}