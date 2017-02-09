// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector LocationToHit, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchVelocityOUT;
	FVector ShotStartFrom = Barrel->GetSocketLocation(FName("ProjectileExitLocation"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this,LaunchVelocityOUT,ShotStartFrom,LocationToHit,
																		LaunchSpeed,
																		ESuggestProjVelocityTraceOption::DoNotTrace
																		);

	if(bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocityOUT.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	///Work out difference between current barrel location and aim direction
	auto AimAsRotator = AimDirection.Rotation();
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto DifInRotation = AimAsRotator - BarrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())
	///move barrel the right amount this frame
	///based on max elevation speed, and frame time 

}
