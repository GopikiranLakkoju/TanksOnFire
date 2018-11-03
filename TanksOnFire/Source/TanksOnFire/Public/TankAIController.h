// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKSONFIRE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

private:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
