// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool isProjectileSuccess = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, hitLocation, launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (isProjectileSuccess)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString tankName = GetOwner()->GetName();
		/*FString ourTank = GetOwner()->GetName();
		FVector barrelLocation = Barrel->GetComponentLocation();*/
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *ourTank, *hitLocation.ToString(), *barrelLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *tankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	Barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = aimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(5);
}

