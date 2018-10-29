// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKSONFIRE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float relativeSpeed);

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSec = 0.1;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxElevationDegrees = 30;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinElevationDegrees = 0;

};
