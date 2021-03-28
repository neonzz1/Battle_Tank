// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
UENUM()
enum class EHealthState : uint8
{
	Full,
	Half,
	Quater
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const; //Returns percentage of health

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetArmorPercent() const;

	FTankDelegate OnTankDeath;

	EHealthState GetHealthState() const;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 120.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 CurrentHealth; //Initilised in beginplay

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 StartingArmor = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 CurrentArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 MaxArmor = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	EHealthState HealthState = EHealthState::Full;

	UFUNCTION()
	void BeginOverlap(AActor* ThisActor, AActor* OtherActor);

private:	

	// Sets default values for this pawn's properties
	ATank();

};
