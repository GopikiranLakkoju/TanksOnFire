// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
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
	UFUNCTION()
		void OnPocessedTankDeath();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// called when AI tank is pocessed
	virtual void SetPawn(APawn* InPawn) override;

	// how close can AI tank can come to hero tank
	UPROPERTY(EditAnyWhere, Category = "Setup")
		float AcceptanceRadius = 3000;
	
};
