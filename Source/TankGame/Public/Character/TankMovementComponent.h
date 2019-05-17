// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankTrack.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void MoveForward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void MoveRight(float Throttle);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)override;

private:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;


};
