// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "../Public/TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	float time = GetWorld()->GetTimeSeconds();
	float elevationChange = relativeSpeed * MaxDegreesPerSec * time;
	UE_LOG(LogTemp, Warning, TEXT("Elevation change %f"), elevationChange);
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	UE_LOG(LogTemp, Warning, TEXT("Raw elevation %f"), rawNewElevation);
	float elevation = FMath::Clamp<float>(rawNewElevation, MaxElevationDegrees, MinElevationDegrees);

	SetRelativeRotation(FRotator(0, 0, elevation));
	UE_LOG(LogTemp, Warning, TEXT("Tank barrel elevation %f"), elevation);
}

