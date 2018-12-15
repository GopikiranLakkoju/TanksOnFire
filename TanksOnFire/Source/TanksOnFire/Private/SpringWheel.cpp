// Fill out your copyright notice in the Description page of Project Settings.

#include "SpringWheel.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
	SetupConstraint();
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
		//UE_LOG(LogTemp, Warning, TEXT("Found parent %s"), *GetAttachParentActor()->GetName());
	}
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

