// © Neonzz Games

#include "TankAimingComponent.h"
#include "Barrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AmmoBooster.h"

#define OUT
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::Initialise(UBarrel* BarrelToSet, UTankTurret* TurretToSet)
{

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::bIsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	return BarrelForward.Equals(AimDirecton, 0.01); //doesn't trigger when barrel is moving using ! makes Aiming never end
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UTankAimingComponent::BeginOverlap);
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo <= 0)
	{
		FireState = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FireState = EFiringStatus::Reloading;
	}
	else if (bIsBarrelMoving()) {
		FireState = EFiringStatus::Aiming;
	}
	else {
		FireState = EFiringStatus::Locked;
	}
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return Ammo;
}

void UTankAimingComponent::BeginOverlap(AActor* ThisActor, AActor* OtherActor)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmmoBooster::StaticClass(), FoundActors);

	for (AActor* TActor : FoundActors)
	{
		AAmmoBooster* AmmoBooster = Cast<AAmmoBooster>(TActor);
		if (AmmoBooster != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AmmoBooster %s"), *AmmoBooster->GetName());

			if (OtherActor == AmmoBooster)
			{
				int32 CurrentAmmo = Ammo;
				int32 AmmoBoost = 5;

				Ammo = CurrentAmmo += AmmoBoost;
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("OnOverlap Ammo"));
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return EFiringStatus();
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector BarrelLocation = Barrel->GetComponentLocation();

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
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	//Always take the shortest route
	if (FMath::Abs(DeltaRotation.Yaw) < 180) {
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotation.Yaw);
	}

}



/*void UTankAimingComponent::TurnTurretTowards(FVector AimDirection)
{

}*/


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) { return; }

	bool bisReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (FireState == EFiringStatus::Locked)
	{
		//Spawn Projectile at socket on barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

		Ammo--;
	}
}