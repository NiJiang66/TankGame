// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;


#define CROSSHAIR_X 0.5f
#define CROSSHAIR_Y 0.3f


/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaSeconds);

	/** 获得控制的坦克 */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	ATank* GetControlledTank();

	void AimToTarget();

	bool GetSightRayHitLocation(FVector& OutHitLocation);

	bool GetLookVectorHitLocaiton(FVector LookDirection, FVector& OutHitLocaiton);

private:

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000.f;

};
