// Copyright Epic Games, Inc. All Rights Reserved.

#include "PocketWorldsUIWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UPocketWorldsUIWheelFront::UPocketWorldsUIWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}