// © Neonzz Games


#include "MortarAIController.h"
#include "Mortar.h"
#include "TankAimingComponent.h"
#include "Tank.h"


float AMortarAIController::ReturnDistanceToPlayer()
{
	if (!PlayerTank)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerTank->GetActorLocation(), ControlledMortar->GetActorLocation());
}

void AMortarAIController::CheckPlayerInRange()
{
	if (!PlayerTank) { return; }

	if (ReturnDistanceToPlayer() <= FireRange)
	{
		AimingComponent->Fire();
		
		UE_LOG(LogTemp, Warning, TEXT("Range Check FIRE!"))
	}
}

void AMortarAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossesedMortar = Cast<AMortar>(InPawn);
}

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireTimeHandle, this, &AMortarAIController::CheckPlayerInRange, FireTime, true);

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	ControlledMortar = Cast<AMortar>(GetPawn());

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank || !ControlledMortar) { return; }

	if (PlayerTank)
	{
		if (!ensure(AimingComponent)) { return; }

		FoundAimingComponent(AimingComponent);

		AimingComponent->AimAt(PlayerTank->GetActorLocation());
	}
}