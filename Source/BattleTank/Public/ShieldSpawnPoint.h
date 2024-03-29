// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ShieldSpawnPoint.generated.h"

class AShieldBooster;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UShieldSpawnPoint : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UShieldSpawnPoint();

	AActor* GetSpawnedActor() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AShieldBooster> ShieldBoosterBlueprint;

	UPROPERTY()
	AShieldBooster* SpawnedActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

};
