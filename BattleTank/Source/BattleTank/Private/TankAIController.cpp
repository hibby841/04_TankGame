// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ThisTank = GetControlledTank();
	if (ThisTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is possessing %s"), *ThisTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is not possessing a tank"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
