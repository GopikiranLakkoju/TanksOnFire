// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "../Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UTankAimingComponent::InitialiseTankAiming(UTankBarrel * tankBarrel, UTankTurret * tankTurret)
{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming initialized"));
	
	if (Barrel || Turret) {
		Barrel = tankBarrel;
		Turret = tankTurret;
	}
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

	// Calculate the OutLaunchVelocity, however there has been some misconception on how this method woks
	// for more info look into: https://community.gamedev.tv/t/suggestprojectilevelocity-is-not-a-bug-working-as-intended-and-heres-why/79193
	bool isProjectileSuccess = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, hitLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
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

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{	
	if (Barrel || Turret) {
		FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator AimAsRotator = aimDirection.Rotation();
		FRotator DeltaRotator = AimAsRotator - BarrelRotator;
		// barrel pitch motion
		Barrel->Elevate(DeltaRotator.Pitch);
		// turret yaw motion
		Turret->Rotate(DeltaRotator.Yaw);	
	}	
}