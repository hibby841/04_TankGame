// Copyright SpaceFerrIT Sudios Ltd.

#include "BattleTank.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTracks * LeftTrackToSet, UTankTracks * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankCurrentForwardDir = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIIntendedMoveVelocity = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankCurrentForwardDir, AIIntendedMoveVelocity));
	IntendTurnRight(FVector::CrossProduct(TankCurrentForwardDir, AIIntendedMoveVelocity).Z);
};

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
};

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
};

