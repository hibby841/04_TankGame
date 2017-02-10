// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//holds barrels properties and elevation method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMinElevation(float NewMinElevationInDegrees);

	//-1 is max downward speed and +1 is max upward speed 
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationInDegrees = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationInDegrees = -10;
};
