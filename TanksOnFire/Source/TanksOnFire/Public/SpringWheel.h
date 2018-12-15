// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

UCLASS()
class TANKSONFIRE_API ASpringWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpringWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// sets the constraint between body and wheels
	void SetupConstraint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Spring Component")
		USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Component")
		USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Component")
		UPhysicsConstraintComponent* MassWheelPhysicsConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Spring Component")
		UPhysicsConstraintComponent* AxleWheelPhysicsConstraint = nullptr;
};
