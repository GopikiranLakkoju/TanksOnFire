// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::SetThrottle(float throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float currrentThrottle)
{
	auto forceApplied = currrentThrottle * TankMaxForce;
	auto wheels = GetWheels();
	auto forcePerWheel = forceApplied / wheels.Num();

	for (ASpringWheel* wheel: wheels)
	{
		wheel->AddDrivingForce(forcePerWheel);
	}
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
	TArray<ASpringWheel*> childComponents;
	TArray<USceneComponent*> children;
	GetChildrenComponents(true, children);
	
	for (USceneComponent* child : children)
	{
		auto spawnPointChild = Cast<USpawnPoint>(child);
		if (spawnPointChild)
		{
			AActor* spawnedChild = spawnPointChild->GetSpawnedActor();
			ASpringWheel* springWheel = Cast<ASpringWheel>(spawnedChild);
			if (springWheel)
			{
				childComponents.Add(springWheel);
			}			
		}
	}
	return childComponents;
}
