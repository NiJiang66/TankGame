// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "TGHelper.h"
#include "TGActorTool.h"
#include "TGCommand.h"
#include "TankAimingComponent.h"

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
