// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp/PickUpBase.h"
#include "PickUpHealth.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API APickUpHealth : public APickUpBase
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(AActor* User)override;

public:

	UPROPERTY(EditAnywhere, category = "PickUp")
	float HealthToAdd = 20.f;

};
