// © Neonzz Games


#include "..\Public\Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Barrel.h"
#include "TankTurret.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}
