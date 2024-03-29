// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay()override;

	virtual void SetPawn(APawn* InPawn)override;

	virtual void Tick(float DeltaTime)override;

	class ATank* GetControlledTank();

	class ATank* GetPlayerTank();

	UFUNCTION()
	void OnControlledTankDeath();


public:

	UPROPERTY(EditAnywhere, Category = "SetUp")
	float AcceptanceRedius = 3000.f;

};
