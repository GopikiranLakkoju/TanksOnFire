// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpringWheel.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKSONFIRE_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	constexpr AActor* GetSpawnedActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	// TSubclassOf can be used to set the child class in blueprint
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<ASpringWheel> SpawnClass;

	UPROPERTY()
		AActor* SpawnedActor = nullptr;	
};
