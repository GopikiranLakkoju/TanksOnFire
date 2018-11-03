// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// hero pawn and tank
	APawn* heroPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATank* heroTank = Cast<ATank>(heroPawn);
	// enemy pawn and tank
	APawn* enemyPawn = GetPawn();
	ATank* enemyTank = Cast<ATank>(enemyPawn);
		
	if (heroTank)
	{
		enemyTank->AimAt(heroTank->GetActorLocation(), enemyTank->LaunchSpeed);
		enemyTank->Fire();
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
		
	/*ATank* playerControlledTank = GetPlayerControllerTank();
	
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found the player: %s"), *playerControlledTank->GetName());
	}*/
}