// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectilrMovement"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(Cast<USceneComponent>(CollisionMesh));
	CollisionMesh->SetNotifyRigidBodyCollision(true);//

	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchParticle"));
	LaunchParticle->SetupAttachment(RootComponent);
	LaunchParticle->SetAutoActivate(true);

	ImpactParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactParticle"));
	ImpactParticle->SetupAttachment(RootComponent);
	ImpactParticle->SetAutoActivate(false);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->SetupAttachment(RootComponent);
	ExplosionForce->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ImpactParticle->Activate();
	CollisionMesh->SetNotifyRigidBodyCollision(false);
	SetRootComponent(ImpactParticle);
	CollisionMesh->DestroyComponent();

	ExplosionForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);
}

