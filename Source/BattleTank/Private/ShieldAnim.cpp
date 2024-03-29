// © Neonzz Games


#include "ShieldAnim.h"

// Sets default values
AShieldAnim::AShieldAnim()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AShieldAnim::BeginPlay()
{
	Super::BeginPlay();

	if (!ShieldAnim) { return; }

	ShieldAnim->SetNotifyRigidBodyCollision(true);
}

// Called every frame
void AShieldAnim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

