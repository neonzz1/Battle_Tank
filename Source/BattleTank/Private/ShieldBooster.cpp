// © Neonzz Games


#include "ShieldBooster.h"
#include "Tank.h"

// Sets default values
AShieldBooster::AShieldBooster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
}

// Called when the game starts or when spawned
void AShieldBooster::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AShieldBooster::BeginOverlap);
}

// Called every frame
void AShieldBooster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShieldBooster::BeginOverlap(AActor* ThisActor, AActor* OtherActor)
{
	auto Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (OtherActor == Player)
	{
		Destroy();
	}
}


