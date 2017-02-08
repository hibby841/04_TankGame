// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ThisTank = GetControlledTank();
	if (ThisTank) 
	{ UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *ThisTank->GetName()); }
	else 
	{ UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank")); }
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
