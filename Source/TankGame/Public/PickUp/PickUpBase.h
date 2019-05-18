// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class TANKGAME_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void UseItem(AActor* User);

public:

	UPROPERTY(VisibleAnywhere,Category = "Custom")
	class UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Custom")
	class USphereComponent* CollisionArea = nullptr;

};
