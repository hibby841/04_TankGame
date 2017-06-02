// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector LocationToHit);

	void AimAtForSky(FVector LookDir);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:

	UTankTurret*Turret = nullptr;

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LineTraceSpeed = 6000;//600 meters per second

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ProjectileLaunchSpeed = 2000;//200 meters per second

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime = 0.0;

	float ReloadTime = 5.0;

	//local barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr;//TODO Remove this

};
