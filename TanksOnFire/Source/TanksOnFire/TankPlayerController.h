// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// forward declaration
class UTankAimingComponent;

/**
 * Responsible for helping the player activities
 */
UCLASS()
class TANKSONFIRE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();
	UTankAimingComponent* TankAimingComponent = nullptr;
protected:
	virtual void BeginPlay() override;
	void GetSightRayHitlocation() const;
	bool GetLookDirection(FVector2D, FVector&, FVector&) const;
	void GetLookVectorHitLocation(FVector, FVector, FVector&) const;
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairLocationX = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairLocationY = 0.333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0;	
	
	UFUNCTION(BlueprintImplementableEvent, category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimingComponent);

private:
};
