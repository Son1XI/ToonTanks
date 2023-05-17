// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	bAlive = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult HitResult;
	bool bHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (bHit)
	{
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::Move(float Value)
{
	float MoveForward = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	const FVector DeltaLocation = FVector(MoveForward, 0.f, 0.f);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	float MoveTurn = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	const FRotator DeltaRotation = FRotator(0.f, MoveTurn, 0.f);
	AddActorLocalRotation(DeltaRotation, true);
}

APlayerController* ATank::GetPlayerController() const
{
	return PlayerController;
}
