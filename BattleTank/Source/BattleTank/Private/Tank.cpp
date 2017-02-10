// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	//no need to protect pointers as they're added at construction
	TankAimingComponent = CreateAbstractDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* MyInputComponent)
{
	Super::SetupPlayerInputComponent(MyInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	 TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector LocationToHit)
{
	TankAimingComponent->AimAt(LocationToHit, LaunchSpeed);
}

