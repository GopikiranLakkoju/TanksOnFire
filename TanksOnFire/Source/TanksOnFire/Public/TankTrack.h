// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKSONFIRE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// sets throttle at -1 to +1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		float TankMaxForce = 40000000; // Assuimg 40 tonnes tank and 1g acceleration
};
