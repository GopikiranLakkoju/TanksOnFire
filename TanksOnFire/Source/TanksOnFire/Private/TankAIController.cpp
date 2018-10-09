// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControllerTank() const
{
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* playerTank = nullptr;
	if (playerPawn)
	{
		playerTank = Cast<ATank>(playerPawn);
	}
	return playerTank;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* heroPlayer = GetPlayerControllerTank();

	if (heroPlayer)
	{
		GetControlledTank()->AimAt(heroPlayer->GetActorLocation());
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
		
	ATank* playerControlledTank = GetPlayerControllerTank();
	
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found the player: %s"), *playerControlledTank->GetName());
	}
}