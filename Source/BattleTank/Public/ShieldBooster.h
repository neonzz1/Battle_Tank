// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShieldBooster.generated.h"

UCLASS()
class BATTLETANK_API AShieldBooster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldBooster();

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* CollisionMesh;
	
	UFUNCTION()
	void BeginOverlap(AActor* ThisActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
