// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float time = GetWorld()->DeltaTimeSeconds;
	float elevationChange = relativeSpeed * MaxDegreesPerSec * time;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	//UE_LOG(LogTemp, Warning, TEXT("Raw elevation %f"), rawNewElevation);
	// clamps the value bw min and max, however due to location and rotation problems of the mesh
	// had to tweak it a bit
	float elevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Tank barrel elevation %f"), elevation);
}