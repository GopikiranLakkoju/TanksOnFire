// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// SpawnActorDeferred delays the BeginPlay of SpringWheel class, which will be
	// initiated only after explict call to UGameplayStatics::FinishSpawningActor
	// meanwile we can do some stuff
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (SpawnedActor)
	{
		SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	}	
}

// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

constexpr AActor * USpawnPoint::GetSpawnedActor()
{
	return SpawnedActor;
}

