// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ThisTank = GetControlledTank();
	if (!ThisTank)
	{ UE_LOG(LogTemp, Warning, TEXT("TankAIController is not possessing a tank")); }
	else
	{ UE_LOG(LogTemp, Warning, TEXT("TankAIController is possessing %s"), *ThisTank->GetName()); }

	auto PlayersTank = GetPlayerTank();
	if (!PlayersTank)
	{ UE_LOG(LogTemp, Warning, TEXT("Didnt find players tank")); }
	else
	{ UE_LOG(LogTemp, Warning, TEXT("Players Tank is %s"), *PlayersTank->GetName()); }

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	if (GetPlayerTank())
	{
		//TODO move towards player

		//aim at player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//TODO fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayersPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayersPawn) { return nullptr; }
	return Cast<ATank>(PlayersPawn);
}
