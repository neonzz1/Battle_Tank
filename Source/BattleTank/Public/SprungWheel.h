// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	
	virtual void Tick(float DeltaTime) override;
	
	void AddDrivingForce(float ForceMagnatude);

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* Constraint;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Axle;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* AxleWheelConstraint;

	float TotalForceMagnatudeThisFrame = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupComponent();

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void ApplyForce();
};
