// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (auto DeadPawn = Cast<ABasePawn>(DeadActor))
	{
		DeadPawn->HandleDestruction();
	}

	if (Cast<ATower>(DeadActor) && --TargetTowers == 0)
	{
		GameOver(true);
	}
	
	if (DeadActor == Tank)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		GameOver(false);
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle TimerHandle;
	FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
	                                                             &AToonTanksPlayerController::SetPlayerEnabledState,
	                                                             true);
	GetWorldTimerManager().SetTimer(TimerHandle, InputDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
