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

	if(UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocityOUT,
		ShotStartFrom,
		LocationToHit,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		))
	{
		auto AimDirection = LaunchVelocityOUT.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s Aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString());
	}
	//if no solution found do nothing
}