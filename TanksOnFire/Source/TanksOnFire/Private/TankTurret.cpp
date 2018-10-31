// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	float time = GetWorld()->DeltaTimeSeconds;
	float elevationChange = relativeSpeed * MaxDegreesPerSec * time;
	float rawNewElevation = RelativeRotation.Yaw + elevationChange;
	//UE_LOG(LogTemp, Warning, TEXT("Raw elevation %f"), rawNewElevation);

	SetRelativeRotation(FRotator(0, rawNewElevation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Tank turret elevation %f"), rawNewElevation);
}