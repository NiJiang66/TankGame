// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "TGActorTool.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTGActorTool : public UObject
{
	GENERATED_BODY()
	
public:

	template<typename T>
	static bool GetFirstActor(UWorld* WorldContextObject, T*& OutActor)
	{
		OutActor = nullptr;
		if (!WorldContextObject) return false;

		for (TActorIterator<AActor> It(WorldContextObject); It; ++It)
		{
			AActor* MidActor = *It;
			if (!MidActor->IsPendingKill())
			{
				if (MidActor->IsA<T>())
				{
					OutActor = Cast<T>(MidActor);
					MidActor = nullptr;
					if (OutActor)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

public:

	UFUNCTION(BlueprintCallable, Category = "ActorTool", meta = (WorldContextObject = "WObj", DeterminesOutputType = "AClass", DynamicOutputParam = "Actor"))
	static bool GetFirstActor_BP(UObject* WObj, TSubclassOf<AActor> AClass, AActor*& Actor);



};
