// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ThisTank = Cast<ATank>(GetPawn());
	if (!ThisTank)
	{ UE_LOG(LogTemp, Warning, TEXT("TankAIController is not possessing a tank")); }
	else
	{ UE_LOG(LogTemp, Warning, TEXT("TankAIController is possessing %s"), *ThisTank->GetName()); }

	auto PlayersTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayersTank)
	{ UE_LOG(LogTemp, Warning, TEXT("Didnt find players tank")); }
	else
	{ UE_LOG(LogTemp, Warning, TEXT("Players Tank is %s"), *PlayersTank->GetName()); }

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	auto PlayersTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayersTank)
	{
		//TODO move towards player

		//aim at player
		ControlledTank->AimAt(PlayersTank->GetActorLocation());

		ControlledTank->Fire();//TODO limit fire rate
	}
}


