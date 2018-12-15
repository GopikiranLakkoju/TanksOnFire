// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.TickGroup = TG_PostPhysics;
	
	MassWheelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelPhysicsConstraint"));
	SetRootComponent(MassWheelPhysicsConstraint);
	
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelPhysicsConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelPhysicsConstraint"));
	AxleWheelPhysicsConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();
	/*Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASpringWheel::OnHit);*/
	SetupConstraint();
}

void ASpringWheel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASpringWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeOnThisFrame);
}

void ASpringWheel::SetupConstraint()
{
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (BodyRoot)
		{
			MassWheelPhysicsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
			AxleWheelPhysicsConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
		}
	}
}

void ASpringWheel::AddDrivingForce(float forceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * forceMagnitude);
	//TotalForceMagnitudeOnThisFrame += forceMagnitude;
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (PrimaryActorTick.TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeOnThisFrame = 0;
	}*/
}

