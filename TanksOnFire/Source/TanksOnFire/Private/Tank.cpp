// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	// if this method is not called, it wont call eventgraph code resided in the blueprint
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{
	if (ensure(Barrel))
	{
		float isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;

		if (isReloaded)
		{
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
			UE_LOG(LogTemp, Warning, TEXT("Projectile working"));
			projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();
		}
	}	
}