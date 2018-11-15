// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Aiming,
	Locked,
	Reloading
};

// Forward declaration 
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKSONFIRE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector hitLocation, float launchSpeed);

	void MoveBarrelTowards(FVector aimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Firing Status")
		EFiringState FiringStatus = EFiringState::Aiming;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitialiseTankAiming(UTankBarrel* tankBarrel, UTankTurret* tankTurret);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
