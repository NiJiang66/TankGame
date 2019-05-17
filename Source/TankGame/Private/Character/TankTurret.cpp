// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
//#include "UnrealMathUtility.h"

void UTankTurret::MoveTurret(FVector AinDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AinDirection.Rotation();

	ChangeYaw = AimRotation.Yaw - CurrentRotation.Yaw;
	if (ChangeYaw > 180.f)
	{
		ChangeYaw -= 360.f;
	}
	else if (ChangeYaw < -180.f)
	{
		ChangeYaw += 360.f;
	}

	float RelativeSpeed = FMath::Clamp<float>(ChangeYaw, -1.f, 1.f);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float NewYaw = RotationChange + RelativeRotation.Yaw;

	SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));

}

float UTankTurret::GetChangeYaw()
{
	return this->ChangeYaw;
}
