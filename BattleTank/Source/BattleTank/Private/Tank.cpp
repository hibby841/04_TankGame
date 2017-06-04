// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed fo blueprint to work

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector LocationToHit)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(LocationToHit, LineTraceSpeed);
}

void ATank::AimAtForSky(FVector LookDir)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAtForSky(LookDir);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	if (IsReloaded) 
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileExitLocation")),
			Barrel->GetSocketRotation(FName("ProjectileExitLocation"))
			);
		Projectile->LaunchProjectile(ProjectileLaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}


