// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void MoveBarrel(FVector AinDirection);

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "SetUp")
		float MaxDegreesPerSecond = 20.f;
	UPROPERTY(EditAnywhere, Category = "SetUp")
		float MaxDegree = 40.f;
	UPROPERTY(EditAnywhere, Category = "SetUp")
		float MinDegree = -1.f;
};
