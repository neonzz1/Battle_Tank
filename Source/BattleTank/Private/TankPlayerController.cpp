// © Neonzz Games

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

#define OUT
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	
	Super::Tick( DeltaTime );

	AimTowardsCrosshair();

	
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //For not possesing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);
	
	OUT FVector HitLocation;

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);

	if (bGotHitLocation){
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	//find crosshair
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	FVector LookDirection;
	

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//Line-trace along look direction

	return false;
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