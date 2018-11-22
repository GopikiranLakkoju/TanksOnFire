// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = GetPawn() != nullptr ? GetPawn()->FindComponentByClass<UTankAimingComponent>() : nullptr;
	if (ensure(TankAimingComponent)) {
		FoundAimingComponent(TankAimingComponent);
	}

	// ATank* controlledTank = GetControlledTank();

	// if (!controlledTank)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("PlayerController is not pocessed"));
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("PlayerController is pocessed %s"), *controlledTank->GetName());
	// }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (ensure(GetPawn()))
	{
		FVector hitLocation;

		GetSightRayHitlocation();
	}

	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s on %s"), *hitLocation.ToString(), *ActorThatTookhit);
}

void ATankPlayerController::GetSightRayHitlocation() const
{
	// find the crosshair position in pixel co-ordinates
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	FVector2D screenLocation = FVector2D(viewPortSizeX * CrosshairLocationX, viewPortSizeY * CrosshairLocationY);
	//UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *screenLocation.ToString());

	FVector LookDirection;
	FVector CameraWorldLocation;
	
	if (GetLookDirection(screenLocation, CameraWorldLocation, LookDirection))
	{
		// line trace along the look direction, and see what we hit (max range)		
		GetLookVectorHitLocation(LookDirection, CameraWorldLocation, LookDirection);
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& CameraWorldLocation, FVector& WorldDirection) const
{
	// deproject and get the direction by converting 2d co-ordinate supplied with 3d co-ordinate
	// returns true if processed
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, CameraWorldLocation, WorldDirection);
}

void ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector cameraWorldLocation, FVector& hitLocation) const
{
	FHitResult hitResult;
	FString hitObject;
	FVector startLocation = cameraWorldLocation;//PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * LineTraceRange);
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_WorldStatic);
	if (isHit)
	{
		hitLocation = hitResult.ImpactPoint;
		hitObject = hitResult.GetActor()->GetName();
		APawn* tank = GetPawn();
		//DrawDebugLine(GetWorld(), hitResult.TraceStart, hitResult.TraceEnd, FColor::Red, false, 0.0, 0.0, 10.0);
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation on Object %s"), *hitObject);
		TankAimingComponent->AimAt(hitLocation);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Raytracing Out of bounds"));
}