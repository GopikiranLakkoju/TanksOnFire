// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement component"));
	// false is not to make the projectile component file, unless fired
	ProjectileMovementComponent->bAutoActivate = false;
}

void AProjectile::LaunchProjectile(float launchSpeed)
{
	float time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Projectile fires at %f"), time, launchSpeed);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * launchSpeed);
	// activates the behavior that we have stopped in constructor and re-initiating again, so it would pick the speed
	ProjectileMovementComponent->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

