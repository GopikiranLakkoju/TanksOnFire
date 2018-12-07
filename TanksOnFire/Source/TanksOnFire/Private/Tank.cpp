// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercentage() const
{
	return (float) CurrentHealth / (float) StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32 roundDamageToInt = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(roundDamageToInt, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 10)
	{
		// broadcasts or executes the methods that are tied to the delegate either by AI or player controller
		OnDeath.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("You are dead!"), CurrentHealth);
	}

	//UE_LOG(LogTemp, Warning, TEXT("CurrentHealth=%i"), CurrentHealth);
	return DamageToApply;
}