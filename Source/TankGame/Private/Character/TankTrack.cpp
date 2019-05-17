// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySideForce();
	ThrottleToDrive = 0;
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = TankMaxDrivingForce * ThrottleToDrive * GetForwardVector();
	FVector ForceLocation = GetSocketLocation(FName("ForceLocaton"));
	//USceneComponent只有Transform和层级，但他的子类UPrimitiveComponent有碰撞和物理，UStaticMeshComponent是他们的子类
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySideForce()
{
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//获得坦克现在的移动速度和侧向
	FVector TAnkVelocity = RootComponent->GetComponentVelocity();
	FVector RightVelocity = RootComponent->GetRightVector();
	//找到坦克侧滑的速度
	float SideSpeed = FVector::DotProduct(TAnkVelocity, RightVelocity);
	//获得坦克侧滑对应地加速度
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	FVector SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*(-1);
	//F = m * a 单条履带的侧向反向需要抵消的力
	FVector CurrectionForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2;

	RootComponent->AddForce(CurrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1, 1);
}
