// © Neonzz Games


#include "ShieldSpawnPoint.h"
#include "ShieldBooster.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UShieldSpawnPoint::UShieldSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
}

AActor * UShieldSpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

// Called when the game starts or when spawned
void UShieldSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AShieldBooster>(ShieldBoosterBlueprint, GetComponentTransform());

	if (!ensure(SpawnedActor)) { return; }

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());

	UE_LOG(LogTemp, Warning, TEXT("SpawnedActor %s"), *SpawnedActor->GetName());
}

// Called every frame
void UShieldSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

