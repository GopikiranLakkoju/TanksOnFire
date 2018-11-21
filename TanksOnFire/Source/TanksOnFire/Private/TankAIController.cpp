// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// hero pawn and tank
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	// enemy pawn and tank
	APawn* enemyPawn = GetPawn();	

	UTankAimingComponent* tankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		
	if (ensure(playerPawn && enemyPawn))
	{
		// move the tank towards hero tank
		MoveToActor(playerPawn, AcceptanceRadius);
		tankAimingComponent->AimAt(playerPawn->GetActorLocation());
		if (tankAimingComponent->GetFiringState() == EFiringState::Aiming)
		{
			tankAimingComponent->Fire();
		}		
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}