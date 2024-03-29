// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

class AShieldBooster;
class AShieldAnim;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const; //Returns percentage of health

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetShieldPercent() const;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AShieldAnim> ShieldAnimBlueprint;

	FTankDelegate OnTankDeath;

	virtual void Tick(float DeltaTime) override;

	void SpawnShield();

	UPROPERTY()
	TArray<AActor*> FoundActor;

	AShieldAnim* ShieldAnim;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 120.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 CurrentHealth; //Initilised in beginplay

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 StartingShield = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int32 CurrentShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 MaxShield = 120.0f;

	UFUNCTION()
	void BeginOverlap(AActor* ThisActor, AActor* OtherActor);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:	

	// Sets default values for this pawn's properties
	ATank();

	FTimerHandle ShieldTimerHandle;

	float ShieldDelay = 0.0415f;

	void ShieldTimerExpired();

};
