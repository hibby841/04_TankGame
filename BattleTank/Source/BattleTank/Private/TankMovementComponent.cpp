// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"


UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//TODO should this tick

											 // ...
};

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throw: %f"), *Name, Throw);
};

