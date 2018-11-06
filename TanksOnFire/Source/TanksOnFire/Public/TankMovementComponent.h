// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward declaration
class UTankTrack;

/**
 *
 Drives the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKSONFIRE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack * leftTrack, UTankTrack * rightTrack);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float push);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float push);

	// check best protection
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
