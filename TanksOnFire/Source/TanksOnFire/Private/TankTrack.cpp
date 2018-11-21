// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// For this to work, "Simulation Generates Hit Events" should be set to true, false by default
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Track hit"));
	//ApplySideForce();
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySideForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionSpeed = -slippageSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionSpeed) / 2;
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1, 1);	
}

void UTankTrack::DriveTrack()
{
	/*FString name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Triggered track at %f"), *name, throttle);*/

	auto forceApplied = GetForwardVector() * CurrentThrottle * TankMaxForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}