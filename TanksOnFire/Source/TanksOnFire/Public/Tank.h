// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKSONFIRE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector hitLocation, float launchSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	UTankMovementComponent* MovementComponent = nullptr;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();

	// Launch speed modifayable, 1000 m/s
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTime = 3; //secs

private:	
	float LastFireTime = 0;
};
