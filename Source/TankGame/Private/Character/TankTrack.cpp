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
	//USceneComponentֻ��Transform�Ͳ㼶������������UPrimitiveComponent����ײ������UStaticMeshComponent�����ǵ�����
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySideForce()
{
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//���̹�����ڵ��ƶ��ٶȺͲ���
	FVector TAnkVelocity = RootComponent->GetComponentVelocity();
	FVector RightVelocity = RootComponent->GetRightVector();
	//�ҵ�̹�˲໬���ٶ�
	float SideSpeed = FVector::DotProduct(TAnkVelocity, RightVelocity);
	//���̹�˲໬��Ӧ�ؼ��ٶ�
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	FVector SideSpeedAcceleration = SideSpeed / DeltaTime * GetRightVector()*(-1);
	//F = m * a �����Ĵ��Ĳ�������Ҫ��������
	FVector CurrectionForce = (RootComponent->GetMass()*SideSpeedAcceleration) / 2;

	RootComponent->AddForce(CurrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1, 1);
}
