// © Neonzz Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShieldAnim.generated.h"

UCLASS()
class BATTLETANK_API AShieldAnim : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldAnim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
