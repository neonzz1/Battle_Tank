// © Neonzz Games


#include "TankAimingComponent.h"

#define OUT
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

		MoveBarrelTowards(AimDirection);
	}

}

	void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
	{
		auto BarrelRotation = Barrel->GetComponentRotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotation = AimAsRotator - BarrelRotation;

		UE_LOG(LogTemp, Warning, TEXT("Aim %s"), *AimAsRotator.ToString());
// FRotator InitialLocation = GetOwner()->GetComponentByName(FNAME("Barrel")); 
// FRotator TargetLocation = FVector(0, 1, 3);
	}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}