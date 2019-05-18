// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "TGHelper.h"
#include "TGActorTool.h"
#include "TGCommand.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"


ATankPlayerController::ATankPlayerController()
{
	CheatClass = UTGCommand::StaticClass();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		TGHelper::DeBug("Erro: Controlled Tank Is NULL");
	}
	else
	{
		TGHelper::DeBug(FString::Printf(TEXT("Controlled Tank Is %s"), *ControlledTank->GetName()));
	}
	ATank* test = nullptr;
	if (UTGActorTool::GetFirstActor<ATank>(GetWorld(), test))
	{
		TGHelper::DeBug("zhaodao yige tank");
	}
	else
	{
		TGHelper::DeBug("meiyou zhaodao tank");
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank)return;
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	AimToTarget();
}

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToTarget()
{
	if (!GetPawn())return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CROSSHAIR_X, ViewportSizeY*CROSSHAIR_Y);

	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		if (GetLookVectorHitLocaiton(WorldDirection, OutHitLocation))
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocaiton(FVector LookDirection, FVector& OutHitLocaiton)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocaiton = HitResult.Location;
		return true;
	}

	OutHitLocaiton = FVector::ZeroVector;
	return false;
}

void ATankPlayerController::OnControlledTankDeath()
{
	PlayerTank = GetControlledTank();

	//StartSpectatingOnly();//进入观察者模式
	PlayerState->bIsSpectator = true;
	ChangeState(NAME_Spectating);
	
	GetWorldTimerManager().SetTimer(TankRespawnHandel, this, &ATankPlayerController::TankRespawn, RespawnTime, false);
}

void ATankPlayerController::TankRespawn()
{
	GetWorldTimerManager().ClearTimer(TankRespawnHandel);

	APlayerStart* FirstStart;
	UTGActorTool::GetFirstActor<APlayerStart>(GetWorld(), FirstStart);

	if (PlayerTank&&FirstStart)
	{
		PlayerTank->ResetTankHealth();
		PlayerTank->SetActorTransform(FirstStart->GetActorTransform());
		Possess(PlayerTank);
		PlayerState->bIsSpectator = false;
		ChangeState(NAME_Playing);
	}
}
