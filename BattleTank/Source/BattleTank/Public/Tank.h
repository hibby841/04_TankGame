// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UTankAimingComponent *TankAimingComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* MyInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void AimAt(FVector LocationToHit);

private:
	UTankBarrel* Barrel = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 1000000;//1000 meters per second TODO find good default
};
