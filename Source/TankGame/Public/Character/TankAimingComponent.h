// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)
enum class EFiringState : uint8 
{
	Reloding,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category = "SetUps")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void Fire();

	void AimAt(FVector HitLocaiton);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "SetUp")
	float TankReloadTime = 3.f;

	UPROPERTY(EditAnywhere, Category = "SetUp")
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditAnywhere, Category = "SetUp")
	TSubclassOf<class AProjectile> ProjectileType;

	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Aiming;

private:

	double LastFireTime = 0;

};
