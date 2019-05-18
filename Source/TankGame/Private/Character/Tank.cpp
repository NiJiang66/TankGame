// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TGHelper.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 MidDamage = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(MidDamage, 0, CurrentHP);
	CurrentHP -= DamageToApply;

	if (CurrentHP <= 0)
	{
		OnTankDeath.Broadcast();
	}
	return CurrentHP;
}

float ATank::GetHealthPercentage()
{
	return (float)CurrentHP / (float)MaxHP;
}

void ATank::ResetTankHealth()
{
	CurrentHP = MaxHP;
}

void ATank::AddTankHealth(int32 HpToAdd)
{
	CurrentHP = FMath::Clamp<int32>((CurrentHP + HpToAdd), 0, MaxHP);
}

