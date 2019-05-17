// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throttle)
{
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(Throttle);
}

void UTankMovementComponent::MoveRight(float Throttle)
{
	LeftTrack->SetThrottle(Throttle);
	RightTrack->SetThrottle(-Throttle);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//获得AI移动/前/右方向
	FVector MoveVelocityNormal = MoveVelocity.GetSafeNormal();
	FVector AIForwardNormal = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIRightNormal = GetOwner()->GetActorRightVector().GetSafeNormal();

	float ForwardSpeed = FVector::DotProduct(MoveVelocityNormal, AIForwardNormal);//-1---1
	float RightSpeed = FVector::DotProduct(MoveVelocityNormal, AIRightNormal);

	MoveForward(ForwardSpeed);
	MoveRight(RightSpeed);

}
