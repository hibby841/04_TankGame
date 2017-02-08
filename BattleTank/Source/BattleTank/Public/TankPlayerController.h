// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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
	
private:

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	bool GetLookDirectionHitLocation(FVector LookDirection, FVector &HitLocationOUT) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirectionOUT) const;

	bool GetSightRayHitLocation(FVector& HitLocationOUT) const;
};
