// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpBase::APickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionArea = CreateDefaultSubobject<USphereComponent>(FName("CollisionArea"));
	CollisionArea->SetSphereRadius(500.f);
	RootComponent = CollisionArea;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionArea->SetGenerateOverlapEvents(true);//����ײ�¼�
	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnOverlap);
}

// Called every frame
void APickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UseItem(OtherActor);
}

void APickUpBase::UseItem(AActor* User)
{
	CollisionArea->SetGenerateOverlapEvents(false);//�ر���ײ�¼�
	this->SetActorHiddenInGame(true);//��������
}

