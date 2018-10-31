// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aim Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel * barrelToSet)
{
	TankAimingComponent->SetBarrelReference(barrelToSet);
	Barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
	TankAimingComponent->SetTurretReference(turretToSet);
}

void ATank::Fire()
{
	FString name = GetWorld()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank fired"));

	if (Barrel)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		UE_LOG(LogTemp, Warning, TEXT("Projectile working"));
	}
}

void ATank::AimAt(FVector hitLocation, float launchSpeed)
{
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}

