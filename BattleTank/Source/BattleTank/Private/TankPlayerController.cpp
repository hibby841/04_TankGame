// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ThisTank = GetControlledTank();
	if (ThisTank) 
	{ UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *ThisTank->GetName()); }
	else 
	{ UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank")); }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;// out parameter
	if (GetSightRayHitLocation(HitLocation))//has side-effect, is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection : %s"), *HitLocation.ToString());
	}

	//get world location of linetrace through crosshair
}

//get world location of linetrace through crosshair, returns true if it hits landscapes or static meshes or anything but sky
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocationOUT) const
{
	HitLocationOUT;//The out Param

	//set crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);//uses out params
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirectionIs : %s"), *LookDirection.ToString());
	}
	//de-project screen position of the crosshair to a world direction
	//then linetrace along that LookDirection, and see what we hit(up to MAX_RANGE)

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirectionOUT) const
{
	FVector CameraWorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirectionOUT);
}
