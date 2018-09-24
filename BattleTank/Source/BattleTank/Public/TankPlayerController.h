// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
*
*/
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3f;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection, FVector& OutWorldLocation) const;
	bool GetLookVectorHitLocation(FVector& LookDirection, FVector& WorldLocation, FVector& OutHitLocation) const;

	float CmToMeters(float& Centimeters) const;
};
