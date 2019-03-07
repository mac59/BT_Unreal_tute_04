// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include"GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
//#include "GameFramework/Actor.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);

	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

	//Find pixel position in screen co-ordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	FVector LookDirection;
	FVector WorldLocation;
	if (GetLookDirection(ScreenLocation, LookDirection, WorldLocation))
	{
		/// UE_LOG(LogTemp, Warning, TEXT("LookDirection %s"), *LookDirection.ToString());
		return GetLookVectorHitLocation(LookDirection, WorldLocation, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection, FVector & OutWorldLocation) const
{
	// "De-project" screen position of the crosshair to a world location
	//FVector WorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutWorldLocation, OutLookDirection));
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& WorldLocation, FVector & OutHitLocation) const
{
	FHitResult HitResult;
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		WorldLocation,
		(LookDirection*LineTraceRange) + WorldLocation,
		ECC_Visibility
		//TraceParameters,
		//FCollisionResponseParams()
	))
	{
		OutHitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit distance %f"), CmToMeters(HitResult.Distance));
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}

float ATankPlayerController::CmToMeters(float & Centimeters) const
{
	return Centimeters/100.0f;
}
