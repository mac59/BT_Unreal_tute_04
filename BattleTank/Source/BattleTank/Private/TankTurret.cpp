// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	///rotate turret

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//auto Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
