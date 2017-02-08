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
		GetControlledTank()->AimAt(HitLocation);
	}

}

//get world location of linetrace through crosshair, returns true if it hits landscapes or static meshes or anything but sky
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocationOUT) const
{
	HitLocationOUT;//The out Param

	//set crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);//uses out params to get screen size

	auto CrossHairScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(CrossHairScreenLocation, LookDirection))
	{
		//then linetrace along that LookDirection, and see what we hit(up to MAX_RANGE)
		if (GetLookDirectionHitLocation(LookDirection, HitLocationOUT))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookDirectionHitLocation(FVector LookDirection, FVector &HitLocationOUT) const
{
	FHitResult HitResult;
	FVector StartPoint = PlayerCameraManager->GetCameraLocation();
	FVector EndPoint = LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility))//if line trace succeeds
	{
		HitLocationOUT = HitResult.Location;
		return true;
	}
	HitLocationOUT = FVector(0);
	return false;//line trace failed
}

//de-project screen position of the crosshair to a WorldDirection(or LookDirection)
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirectionOUT) const
{
	FVector CameraWorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirectionOUT);
}
