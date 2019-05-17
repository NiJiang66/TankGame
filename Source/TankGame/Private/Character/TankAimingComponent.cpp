// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TGHelper.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Barrel || !Turret)return;

	if ((FPlatformTime::Seconds() - LastFireTime) < TankReloadTime)
	{
		FiringState = EFiringState::Reloding;
		return;
	}

	if (FMath::Abs(Turret->GetChangeYaw()) > 1)
	{
		FiringState = EFiringState::Aiming;
	}
	else if (FMath::Abs(Turret->GetChangeYaw()) <= 1)
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	bool bIsReload = (FPlatformTime::Seconds() - LastFireTime) > TankReloadTime;
	if (!bIsReload)return;
	TGHelper::DeBug("Fire");
	if (!Barrel || !Turret)return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileType,
		Barrel->GetSocketLocation(FName("FireLocation")),
		Barrel->GetSocketRotation(FName("FireLocation"))
		);
	Projectile->LaunchProjectile(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();

}

void UTankAimingComponent::AimAt(FVector HitLocaiton)
{
	if (Barrel == nullptr || Turret == nullptr)
		return;

	FVector FireVector;
	FVector StartLocation = Barrel->GetSocketLocation("FireLocaiton");

	bool bHaveSolution = false;
	bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		FireVector,
		StartLocation,
		HitLocaiton,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	FireVector.Normalize();
	if (bHaveSolution)
	{
		//Í¨ÖªÅÚ¹ÜÅÚËþ
		Turret->MoveTurret(FireVector);
		Barrel->MoveBarrel(FireVector);
	}
}

