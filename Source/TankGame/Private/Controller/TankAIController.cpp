// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TGHelper.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (ControlledTank == nullptr)
	{
		TGHelper::DeBug("Erro: Controlled Tank Is NULL");
	}
	else
	{
		TGHelper::DeBug(FString::Printf(TEXT("Controlled Tank Is %s"), *ControlledTank->GetName()));
	}
	
	if (PlayerTank)
	{
		TGHelper::DeBug("zhaodao WanJia kognzhi de tanke ");
	}
	else
	{
		TGHelper::DeBug("meiyou zhaodao tank");
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank)return;
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnControlledTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetControlledTank()&& GetPlayerTank())
	{
		//向玩家移动
		MoveToActor(GetPlayerTank(), AcceptanceRedius);

		float Distance = FVector::Distance(GetPlayerTank()->GetActorLocation(), GetControlledTank()->GetActorLocation());
		if (Distance > AcceptanceRedius)return;

		//开火
		UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
		if (AimingComponent->FiringState == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

class ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::OnControlledTankDeath()
{
	if (GetControlledTank())
	{
		GetControlledTank()->DetachFromControllerPendingDestroy();
		//GetControlledTank()->Destroy();
	}
}
