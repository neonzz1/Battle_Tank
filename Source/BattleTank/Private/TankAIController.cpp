// © Neonzz Games

#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

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
		//TODO Move towards player

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		//Fires when bisReloaded is true within tank
		ControlledTank->Fire();

	}


}
