// Copyright SpaceFerrIT Sudios Ltd.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	//how close can AI get
	float AcceptanceRadius = 3000;


};
