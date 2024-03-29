// © Neonzz Games
//TODO Have a shield animation

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "EngineUtils.h"
#include "Barrel.h"
#include "TankTurret.h"
#include "ShieldBooster.h"
#include "ShieldAnim.h"
#include "ShieldSpawnPoint.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
}

float ATank::GetShieldPercent() const
{
	return (float)CurrentShield / (float)MaxShield;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmmount); // Changes DamageAmmount to int32

	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth); //Clamp changed DamageAmmount

	if (CurrentShield != 0)
	{
		CurrentShield -= DamageToApply;
	}
	else
	{
		CurrentHealth -= DamageToApply;
	}

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

	CurrentShield = StartingShield;

	OnActorBeginOverlap.AddDynamic(this, &ATank::BeginOverlap);
	
	SpawnShield();

	ShieldAnim->Destroy();

	GetWorld()->GetTimerManager().SetTimer(ShieldTimerHandle, this, &ATank::ShieldTimerExpired, ShieldDelay, true);
}
//Overlap
void ATank::BeginOverlap(AActor* ThisActor, AActor* OtherActor)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShieldBooster::StaticClass(), FoundActor);
	
	for  (AActor* TActor : FoundActor)
	{
		AShieldBooster* ShieldBooster = Cast<AShieldBooster>(TActor);

		if (ShieldBooster != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ShieldBooster %s"), *ShieldBooster->GetName());

			if (OtherActor == ShieldBooster)
			{
				int32 ShieldBoost = 20;
				
				CurrentShield = CurrentShield += ShieldBoost;

				CurrentShield = FMath::Clamp<int32>(CurrentShield, 0, MaxShield);
			}
		}
	}
}

void ATank::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SpawnShield()
{
	USceneComponent* TankRoot = GetRootComponent();

	ShieldAnim = GetWorld()->SpawnActor<AShieldAnim>(
		ShieldAnimBlueprint,
		TankRoot->GetSocketLocation(FName("Shield Anim")),
		TankRoot->GetSocketRotation(FName("Shield Anim"))
		);
}

void ATank::ShieldTimerExpired()
{
	if (CurrentShield >= 20.0f)
	{
		ShieldAnim->Destroy();

		SpawnShield();
	}
	else
	{
		ShieldAnim->Destroy();
	}
}