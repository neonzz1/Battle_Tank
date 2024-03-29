// © Neonzz Games

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"
#include "AmmoBooster.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle, this, &ATankAIController::FireTimerExpired, FireTime, true);

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

	ControlledTank = Cast<ATank>(GetPawn());
	
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
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

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (!PlayerTank || !ControlledTank) { return; } // removed ensure for Player Death

	if (PlayerTank) 
	{
		auto FireState = AimingComponent->GetFiringState();

		if (FireState != EFiringStatus::OutOfAmmo)
		{
			MoveToActor(PlayerTank, AcceptanceRadius);
			//TODO check value is in cm

			if (!ensure(AimingComponent)) { return; }

			FoundAimingComponent(AimingComponent);

			AimingComponent->AimAt(PlayerTank->GetActorLocation());
		}
		
		else if (FireState == EFiringStatus::OutOfAmmo)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmmoBooster::StaticClass(), FoundActors);

			for (AActor* TActor : FoundActors)
			{
				AAmmoBooster* AmmoBooster = Cast<AAmmoBooster>(TActor);

				if (AmmoBooster != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Ammoboost %s"), *AmmoBooster->GetName());

					if (MoveToActor(AmmoBooster, AcceptanceRadius))
					{
						UE_LOG(LogTemp, Warning, TEXT("MoveToActor Success Moving to: %s"), *AmmoBooster->GetName());
					}
				}
			}
		}
	}
}

void ATankAIController::FireTimerExpired()
{
	if (!PlayerTank) { return; }

	AimingComponent->Fire();

	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}
