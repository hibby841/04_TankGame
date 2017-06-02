// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//TODO should this tick

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector LocationToHit, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchVelocityOUT;
	FVector ShotStartFrom = Barrel->GetSocketLocation(FName("ProjectileExitLocation"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,LaunchVelocityOUT,ShotStartFrom,LocationToHit,
																		LaunchSpeed,
		                                                                false,
		                                                                0,
		                                                                0,
																		ESuggestProjVelocityTraceOption::DoNotTrace//so many versions later and the bugs still here
																		);

	if(bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocityOUT.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		FRotator LookDirOUT;
		FVector Location;
		auto *player = GetWorld()->GetFirstPlayerController();
		player->GetPlayerViewPoint(Location, LookDirOUT);
		MoveBarrelTowards(LookDirOUT.Vector());
	}

}

void UTankAimingComponent::AimAtForSky(FVector LookDir)
{
	MoveBarrelTowards(LookDir);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) { return;}

	///Work out difference between current barrel location and aim direction
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto DifInRotation = AimAsRotator - BarrelRotation;
	///move barrel the right amount this frame
	///based on max elevation speed, and frame time 
	Barrel->ElevateBarrel(DifInRotation.Pitch);
	Turret->RotateTurret(DifInRotation.Yaw);
}


