// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include"Tank.h"
#include "TankPlayerController.h"


// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ThisTank = GetControlledTank();
	if (!ThisTank) 
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

	FVector HitLocation;//will either be the look direction or the hit location
	if (GetSightRayHitLocation(HitLocation))//has side-effect, is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	else 
	{
		GetControlledTank()->AimAtForSky(HitLocation);
	}

}

//get world location of linetrace through crosshair, returns true if it hits landscapes or static meshes or anything but sky
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocationOUT) const
{	
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		//then linetrace along that LookDirection, and see what we hit(up to MAX_RANGE)
		if (GetLookDirectionHitLocation(LookDirection, HitLocationOUT))
		{
			return true;
		}
	}
	HitLocationOUT = LookDirection;
	return false;
}

bool ATankPlayerController::GetLookDirectionHitLocation(FVector LookDirection, FVector &HitLocationOUT) const
{
	FHitResult HitResult;
	FVector StartPoint = PlayerCameraManager->GetCameraLocation();
	FVector EndPoint = LookDirection * LineTraceRange;
	FCollisionQueryParams queryparams = FCollisionQueryParams(FName(""), false, GetControlledTank());
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_MAX, queryparams))//if line trace succeeds
	{
		HitLocationOUT = HitResult.Location;
		return true;
	}
	HitLocationOUT = FVector(0);
	return false;//line trace failed
}

//de-project screen position of the crosshair to a WorldDirection(or LookDirection)
bool ATankPlayerController::GetLookDirection(FVector &LookDirectionOUT) const
{
	//set crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);//uses out params to get screen size

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector CameraWorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirectionOUT);
}
