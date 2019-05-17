// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::MoveBarrel(FVector AinDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AinDirection.Rotation();

	float ChangePitch = AimRotation.Pitch - CurrentRotation.Pitch;

	float RelativeSpeed = FMath::Clamp<float>(ChangePitch, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float NewPitch = RotationChange + RelativeRotation.Pitch;
	//Limitation of pitch
	NewPitch = FMath::Clamp<float>(NewPitch, MinDegree, MaxDegree);

	SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));
}