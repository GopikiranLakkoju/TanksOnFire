// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack)
{	
	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float push)
{
	if (!LeftTrack || !RightTrack)
	{	
		return;
	}	
	//UE_LOG(LogTemp, Warning, TEXT("Movement push is %f"), push);
	LeftTrack->SetThrottle(push);
	RightTrack->SetThrottle(push);
}

void UTankMovementComponent::IntendTurnRight(float push)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Movement right is %f"), push);
	LeftTrack->SetThrottle(-push);
	RightTrack->SetThrottle(-push);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector tankForward = GetOwner()->GetActorForwardVector();
	FVector aiForwardIntension = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("Tank name: %s with velocity: %s"), *tankName, *moveVelocity);
	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntension);
	IntendMoveForward(forwardThrow);
}
