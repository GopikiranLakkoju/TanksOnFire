// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKSONFIRE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;
	// multicast delegate, used for braodcasting client  methods
	FTankDelegate OnDeath;

protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Damage")
		int32 CurrentHealth;
};