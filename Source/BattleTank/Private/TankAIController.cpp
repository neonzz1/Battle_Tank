// © Neonzz Games

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Ai Controller"));
}
void ATankAIController::Tick(float DeltaTime) {
	
	Super::Tick( DeltaTime );
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank || !ControlledTank) { return; }

	if (PlayerTank) {
		
		MoveToActor(PlayerTank, AcceptanceRadius);
		//TODO check value is in cm
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fires when bisReloaded is true within tank
		ControlledTank->Fire();

	}


}
