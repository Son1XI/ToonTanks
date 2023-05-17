// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

	void CheckFireCondition();
	bool IsTargetInRange() const;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY()
	ATank* Tank;
};
