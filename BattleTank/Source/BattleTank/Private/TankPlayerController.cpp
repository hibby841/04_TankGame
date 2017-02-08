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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
	}

	//get world location of linetrace through crosshair
}

//get world location of linetrace through crosshair, returns true if it hits landscapes or static meshes or anything but sky
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocationOUT) const
{
	HitLocationOUT = FVector(1.0);//out Param

	return true;
}