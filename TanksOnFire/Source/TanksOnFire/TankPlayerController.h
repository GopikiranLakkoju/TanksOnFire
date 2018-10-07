// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT

/**
 * 
 */
UCLASS()
class TANKSONFIRE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();	

protected:
	virtual void BeginPlay() override;
	bool GetSightRayHitlocation(FVector&) const;
	bool GetLookDirection(FVector2D, FVector&, FVector&) const;
	UPROPERTY(EditAnywhere)
		float CrosshairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairLocationY = 0.333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0;
	bool GetLookVectorHitLocation(FVector, FVector, FVector&) const;
};