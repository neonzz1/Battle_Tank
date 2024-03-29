// © Neonzz Games


#include "ShieldAnimSpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UShieldAnimSpawnPoint::UShieldAnimSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UShieldAnimSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AShieldAnim>(ShieldAminBlueprint, GetComponentTransform());

	if (!ensure(SpawnedActor)) { return; }

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void UShieldAnimSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor * UShieldAnimSpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

