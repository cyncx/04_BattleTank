// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"


void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}

