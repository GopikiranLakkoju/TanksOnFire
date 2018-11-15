// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UTankAimingComponent* aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (aimingComponent) {
		FoundAimingCompnent(aimingComponent);
	}	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller didn't find aim component"));
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
	if (!GetControlledTank())
		return;

	FVector hitLocation;

	GetSightRayHitlocation();

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
	// deproject and get the direction by converting 2d co-ordinate supplied with 3d co-ordinate
	// returns true if processed
	if (GetLookDirection(screenLocation, CameraWorldLocation, LookDirection))
	{
		// line trace along the look direction, and see what we hit (max range)		
		GetLookVectorHitLocation(LookDirection, CameraWorldLocation, LookDirection);
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& CameraWorldLocation, FVector& WorldDirection) const
{	
	bool is3dposition = DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, CameraWorldLocation, WorldDirection);
	if (is3dposition)
	{
		//UE_LOG(LogTemp, Warning, TEXT("3d position Direction: %s"), *WorldDirection.ToString());
	}
	return is3dposition;
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
		ATank* tank = GetControlledTank();
		//DrawDebugLine(GetWorld(), hitResult.TraceStart, hitResult.TraceEnd, FColor::Red, false, 0.0, 0.0, 10.0);
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s on Object %s"), *hitLocation.ToString(), *hitObject);
		tank->AimAt(hitLocation, tank->LaunchSpeed);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Raytracing Out of bounds"));
}
