// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* Constraint;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* Wheel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupComponent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
