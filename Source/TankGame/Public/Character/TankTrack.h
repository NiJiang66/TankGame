// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	void ApplySideForce();

	/** 设置油门的值，规定输入值在-1到1区间 */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

public: 

	/** 最大驱动马力 */
	UPROPERTY(EditAnywhere, Category = "SetUp")
	float TankMaxDrivingForce = 40000000.f;

	/** 油门值 */
	float ThrottleToDrive = 0;
};
