// © Neonzz Games

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
	

	//UE_LOG(LogTemp, Warning, TEXT("Ai Controller"));
}
void ATankAIController::Tick(float DeltaTime) {
	
	Super::Tick( DeltaTime );
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) { return; }

	if (PlayerTank) {

		MoveToActor(PlayerTank, AcceptanceRadius);
		//TODO check value is in cm
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		if (!ensure(AimingComponent)) { return; }

		FoundAimingComponent(AimingComponent);

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		AimingComponent->Fire();
		}

	}
