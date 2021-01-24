// © Neonzz Games

#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Ai Controller"));

	auto AiTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!AiTank) {

		UE_LOG(LogTemp, Error, TEXT("No AI Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Ai Controlling %s"), *AiTank->GetName());
	}

	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("No Player Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aiming At %s"), *PlayerTank->GetName());
	}
}
void ATankAIController::Tick(float DeltaTime) {
	
	Super::Tick( DeltaTime );
	auto AiTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) { return; }

	if (GetPlayerTank()) {
		//TODO Move towards player

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//fire

	}
	//TODO Move towards player

	
	//fire

}
ATank * ATankAIController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() {
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);

}