// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	bool GetLookDirection(FVector &LookDirectionOUT) const;//needed public to allow aiming at sky
	
private:

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.4;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	bool GetLookDirectionHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

	bool GetSightRayHitLocation(FVector& HitLocationOUT) const;
};
