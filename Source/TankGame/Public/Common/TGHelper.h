// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"


namespace TGHelper 
{
	UFUNCTION(BlueprintCallable,Category = "TGHelper")
	FORCEINLINE void DeBug(FString Message, ELogVerbosity::Type Typ = ELogVerbosity::Display, float Duration = 3.f, FColor Color = FColor::Red, int Key = -1)
	{
		GLog->Log(Typ, Message);

		if (GEngine && Duration >= 0)
		{
			//GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Message);
		}
	}



}