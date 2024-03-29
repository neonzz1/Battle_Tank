// © Neonzz Games


#include "AmmoBooster.h"
#include "tank.h"
#include "TankAimingComponent.h"

// Sets default values
AAmmoBooster::AAmmoBooster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
}

// Called when the game starts or when spawned
void AAmmoBooster::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AAmmoBooster::BeginOverlap);
}

void AAmmoBooster::BeginOverlap(AActor* ThisActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OtherActor %s"), *OtherActor->GetName());

	ATank* Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (OtherActor == Player)
	{
		Destroy();
	}
}


// Called every frame
void AAmmoBooster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


