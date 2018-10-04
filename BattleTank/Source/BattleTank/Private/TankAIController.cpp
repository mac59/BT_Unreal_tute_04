// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	///UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController posessing: %s"), *(ControlledTank->GetName()));
	}

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Cann't find player Tank"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI can find: %s"), *PlayerTank->GetName());
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EngageTarget();
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI can find: %s"), *PlayerController->getna);
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}


}

void ATankAIController::EngageTarget()
{
	if (GetPlayerTank())
	{
		// TODO Move towards the player

		//Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//Fire if ready
	}
}
