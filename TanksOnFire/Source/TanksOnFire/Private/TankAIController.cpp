// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"


ATank* ATankAIController::GetPlayerControlledTank() const
{
	APawn* payerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* playerTank = nullptr;
	if (payerPawn)
	{
		playerTank = Cast<ATank>(payerPawn);
	}
	return playerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
		
	ATank* playerControlledTank = GetPlayerControlledTank();
	
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found the player: %s"), *playerControlledTank->GetName());
	}
}

