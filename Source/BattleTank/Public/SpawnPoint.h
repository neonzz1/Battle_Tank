// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	AActor* GetSpawnedActor() const { return SpawnedActor; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASprungWheel> SprungWheelBlueprint;

	UPROPERTY()
	ASprungWheel* SpawnedActor;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;
		
};
