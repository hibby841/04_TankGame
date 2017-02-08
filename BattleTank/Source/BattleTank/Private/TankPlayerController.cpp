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
	//get world location of linetrace through crosshair
}