// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * Set Max movement speeds for the tracks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000;//assume 40 ton tank
};
