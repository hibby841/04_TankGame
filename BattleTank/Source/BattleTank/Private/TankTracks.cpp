// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"

void UTankTracks::SetThrottle(float throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, throttle);

	// TODO clamp actual throttle input
	auto ForceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

