// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKSONFIRE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Damage")
		int32 CurrentHealth = StartingHealth;
};
