// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankaDelegate);

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();

	void ResetTankHealth();

	void AddTankHealth(int32 HpToAdd);

public:

	FTankaDelegate OnTankDeath;

private:

	UPROPERTY(EditAnywhere, Category = "SetUp")
	int32 MaxHP = 100;
	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	int32 CurrentHP = MaxHP;

};
