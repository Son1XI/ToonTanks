// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Particles")
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Particles")
	UParticleSystemComponent* TrailPS;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Sound")
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Sound")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditDefaultsOnly);
	float Damage = 50.f;
};
