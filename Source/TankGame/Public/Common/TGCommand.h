// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TGCommand.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTGCommand : public UCheatManager
{
	GENERATED_BODY()
public:

	UFUNCTION(exec)
		void TestCommand();
};
