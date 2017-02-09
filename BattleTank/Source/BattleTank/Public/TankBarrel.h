// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//holds barrels properties and elevation method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void ElevateBarrel(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere)
	float MaxElevationInDegrees = 40;
	UPROPERTY(EditAnywhere)
	float MinElevationInDegrees = -10;
};
