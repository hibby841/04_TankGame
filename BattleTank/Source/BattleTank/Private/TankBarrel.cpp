// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	auto ElevateChange = (FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevateChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("Moving Barrel"));
}

