// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitialiseMovement(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("Initialised movement for: %s"), *TankName);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Log, TEXT("Throw: %f"), Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//UE_LOG(LogTemp, Log, TEXT("Throw: %f"), Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AITankForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	auto AITankRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveForward(AITankForwardThrow);
	IntendTurnRight(AITankRightThrow);
}
