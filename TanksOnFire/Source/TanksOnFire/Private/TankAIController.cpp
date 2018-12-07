// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// hero pawn and tank
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	// enemy pawn and tank
	APawn* enemyPawn = GetPawn();	

	UTankAimingComponent* tankAimingComponent = enemyPawn->FindComponentByClass<UTankAimingComponent>();
		
	if (playerPawn)
	{
		// move the tank towards hero tank
		MoveToActor(playerPawn, AcceptanceRadius);
		tankAimingComponent->AimAt(playerPawn->GetActorLocation());
		if (tankAimingComponent->GetFiringState() == EFiringState::Aiming)
		{
			//UE_LOG(LogTemp, Warning, TEXT("AI tank name: %s fires at time: %f"), *enemyPawn->GetName(), tankAimingComponent->LastFireTime);
			tankAimingComponent->Fire();
		}		
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* pocessedTank = Cast<ATank>(InPawn);
		if (pocessedTank)
		{
			// subscribe local method on tank's death event
			pocessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPocessedTankDeath);
		}
	}
}

void ATankAIController::OnPocessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI %s is dead"), *GetName());
	APawn* aiPawn = GetPawn();
	if (aiPawn)
	{
		aiPawn->DetachFromControllerPendingDestroy();
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}