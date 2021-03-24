// © Neonzz Games


#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Barrel.h"
#include "TankTurret.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

EHealthState ATank::GetHealthState() const
{
	return EHealthState();
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmmount); // Changes DamageAmmount to int32

	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth); //Clamp changed DamageAmmount

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnTankDeath.Broadcast();
	}
	
	return DamageToApply;
}

// Sets default values


void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth <= 25)
	{
		EHealthState::Quater;
	}

	else if (CurrentHealth == 60)
	{
		EHealthState::Half;
	}

	else {
		EHealthState::Full;
	}
}