// © Neonzz Games

#include "TankAimingComponent.h"
#include "Barrel.h"
#include "TankTurret.h"

#define OUT
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Barrel || !Turret) { return; }


	auto InitialTurretRotation = Turret->GetComponentRotation();

}
void UTankAimingComponent::Initialise(UBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret) { return; }
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

		//UE_LOG(LogTemp, Warning, TEXT("%f Aim solution Found"), Time);

		MoveBarrelTowards(AimDirection);

		TurnTurretTowards(AimDirection);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f No aim solution"), Time);

		auto GetCurrentElevation = Barrel->GetComponentRotation();
		auto ReturnToInitalElevation = GetCurrentElevation - InitialElevation;

		auto GetCurrentRotation = Turret->GetComponentRotation();
		auto ReturnToInitialRotation = GetCurrentRotation - InitialTurretRotation;

		Barrel->Elevate(ReturnToInitalElevation.Pitch); //TODO make this work
		Turret->Rotate(ReturnToInitialRotation.Yaw); //TODO make this work
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) { return; }
	auto BarrelRotation = Barrel->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
}



void UTankAimingComponent::TurnTurretTowards(FVector AimDirection)
{
	if (!Turret) { return; }
	auto TurretRotation = Turret->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotator - TurretRotation;

	Turret->Rotate(DeltaRotation.Yaw);
}