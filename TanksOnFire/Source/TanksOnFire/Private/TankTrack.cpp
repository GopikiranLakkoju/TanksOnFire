// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	/*FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Triggered track at %f"), *name, throttle);*/

	auto forceApplied = GetForwardVector() * throttle * TankMaxForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}