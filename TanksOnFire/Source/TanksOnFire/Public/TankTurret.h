// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	void Rotate(float relativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSec = 25;
};
