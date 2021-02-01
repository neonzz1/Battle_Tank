// © Neonzz Games

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

#define OUT
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetControlledTank();
	
	if (!ensure(PlayerTank)) {
		UE_LOG(LogTemp, Error, TEXT("No Tank"));
	}
	auto AimingComponent = PlayerTank->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else { UE_LOG(LogTemp, Error, TEXT("NoAiming")); return; }

	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	
	Super::Tick( DeltaTime );

	AimTowardsCrosshair();

	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) {	return; }
	
	OUT FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)){
		GetControlledTank()->AimAt(HitLocation);
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	auto PlayerPawn = GetPawn();
	if (!ensure(PlayerPawn)) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	//find crosshair
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	FVector LookDirection;
	

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//Line-trace along look direction

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const 
{
	
	FVector CameraWorldLocation; //To be discarded

	//De-projecr the screen position of crosshair to world direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
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
		ECollisionChannel::ECC_Visibility))
	{
		OUT HitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}

}