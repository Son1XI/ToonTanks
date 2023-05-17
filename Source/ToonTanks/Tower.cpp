// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsTargetInRange())
	{
		RotateTurret(Tank->GetActorLocation());	
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (IsTargetInRange() && Tank && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::IsTargetInRange() const
{
	if (!Tank) return false;

	if (FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange)
	{
		return true;
	}

	return false;
}
