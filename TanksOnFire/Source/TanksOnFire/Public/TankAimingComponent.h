// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankBarrel.h"
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
	void AimAt(FVector hitLocation);
	void MoveBarrelTowards(FVector aimDirection);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool IsBarrelMoving();

	UPROPERTY(BlueprintReadOnly, Category = "Firing Status")
		EFiringState FiringStatus = EFiringState::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void InitialiseTankAiming(UTankBarrel* tankBarrel, UTankTurret* tankTurret);

	// Launch speed modifayable, 1000 m/s
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTime = 3; //secs

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	float LastFireTime = 0;
	FVector AimDirection;
	float worldTimeline = 0;
};
