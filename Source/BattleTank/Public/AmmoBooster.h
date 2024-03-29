// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBooster.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API AAmmoBooster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBooster();
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	UStaticMeshComponent* CollisionMesh;

	UFUNCTION()
	void BeginOverlap(AActor* ThisActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AAmmoBooster> AmmoBoosterBlueprint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
