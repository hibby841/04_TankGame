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

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector LocationToHit, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector LaunchVelocityOUT;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileExitLocation"));
	const TArray < AActor * > &ActorsToIgnore{GetWorld()->GetFirstPlayerController()->GetParentActor()};
	FCollisionResponseParams ResponseParam;
	//calculate launch velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		LaunchVelocityOUT,
		StartLocation,
		LocationToHit,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::TraceFullPath
	);
	if(bHaveAimSolution)
	{
		auto TankName = GetOwner()->GetName();
		auto AimDirection = LaunchVelocityOUT.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at : %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and aim direction
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DifInRotation = AimAsRotator - BarrelRotation;
	//move the barrel the right amount this frame
	//given a max elevation speed, and frame time
}