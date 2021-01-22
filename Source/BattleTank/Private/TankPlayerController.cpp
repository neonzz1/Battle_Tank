// © Neonzz Games

#include "Engine/World.h"
#include "TankPlayerController.h"

#define OUT
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

void ATankPlayerController::Tick(float DeltaTime)
{
	
	Super::Tick( DeltaTime );

	AimTowardsCrosshair();

	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {	return; }
	
	OUT FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)){
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation %s"), *HitLocation.ToString());
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	auto PlayerPawn = GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	//find crosshair
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	FVector CameraWorldLocation;
	FVector LookDirection;
	

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		
		UE_LOG(LogTemp, Warning, TEXT("Looking at %s"), *LookDirection.ToString());
		//GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//Line-trace along look direction
	//getlookvectorhit

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const 
{
	
	FVector CameraWorldLocation; //To be discarded

	//De-projecr the screen position of crosshair to world direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		LookDirection,
		CameraWorldLocation
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto Start = PlayerCameraManager->GetCameraLocation();
	auto End = FVector(LookDirection * LineTraceRange);


	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}

}