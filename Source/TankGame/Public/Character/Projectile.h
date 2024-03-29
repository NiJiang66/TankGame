// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* LaunchParticle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* ImpactParticle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	float ProjectileDamage = 20.f;
};	
