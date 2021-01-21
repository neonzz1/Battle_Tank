// © Neonzz Games

#include "Engine/World.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller"));

	auto PlayerTank = GetControlledTank();
	
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("No Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlling %s"), *PlayerTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Ticking"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	auto PlayerPawn = GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}