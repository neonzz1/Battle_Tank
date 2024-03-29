// © Neonzz Games


#include "Mortar.h"

// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMortar::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = StartingHealth;
}

float AMortar::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

EHealthStateM AMortar::GetHealthState() const
{
	return EHealthStateM();
}

float AMortar::TakeDamage(float DamageAmmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmmount); // Changes DamageAmmount to int32

	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth); //Clamp changed DamageAmmount

	CurrentHealth -= DamageToApply;
	
	if (CurrentHealth <= 0)
	{
		Destroy();
	}

	return DamageToApply;
}

// Called every frame
void AMortar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


