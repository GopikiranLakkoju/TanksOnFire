// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "../Public/TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	float time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevate() at %f"), time, relativeSpeed);
}

