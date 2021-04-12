// © Neonzz Games

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "Mortar.h"
#include "AmmoBooster.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
	
	TActorIterator<AAmmoBooster> AmmoBoost = TActorIterator<AAmmoBooster>(GetWorld());
	

	//UE_LOG(LogTemp, Warning, TEXT("Ai Controller"));
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		PossesedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
		UE_LOG(LogTemp, Warning, TEXT("AI PAWN SET"));
	}
}

void ATankAIController::OnPossesedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Ai death"));

	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime) {
	
	Super::Tick( DeltaTime );
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank || !ControlledTank) { return; } // removed ensure for Player Death

	if (PlayerTank) {
		
		MoveToActor(PlayerTank, AcceptanceRadius);
		//TODO check value is in cm
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		if (!ensure(AimingComponent)) { return; }

		FoundAimingComponent(AimingComponent);

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		AimingComponent->Fire();

		auto FireStae = AimingComponent->GetFiringState();

		if (FireStae == EFiringStatus::OutOfAmmo)
		{
			//MoveToActor();
		}

		}

	}
