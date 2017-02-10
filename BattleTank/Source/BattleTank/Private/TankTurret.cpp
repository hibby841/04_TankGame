// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::RotateTurret(float RelativeSpeed)
{
	auto RotationChange = (FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}

