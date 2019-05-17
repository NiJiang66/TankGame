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

	/** �������ŵ�ֵ���涨����ֵ��-1��1���� */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

public: 

	/** ����������� */
	UPROPERTY(EditAnywhere, Category = "SetUp")
	float TankMaxDrivingForce = 40000000.f;

	/** ����ֵ */
	float ThrottleToDrive = 0;
};
