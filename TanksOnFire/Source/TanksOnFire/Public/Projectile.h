// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKSONFIRE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	// launches the projectile at what rate
	void LaunchProjectile(float launchSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle Setup")
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Particle Setup")
		UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Particle Setup")
		UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Particle Setup")
		URadialForceComponent* ExplosionForce = nullptr;

	// this can also be done in code through, OnComponentHit from CollisionMesh
	// its same as calling this method from blueprint 
	UFUNCTION(BlueprintCallable, Category = "Particle System")
	void ShowImpactWithParticleEffect();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void AttachementsForProjectile();
};