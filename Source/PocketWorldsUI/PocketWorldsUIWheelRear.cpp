// Copyright Epic Games, Inc. All Rights Reserved.

#include "PocketWorldsUIWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UPocketWorldsUIWheelRear::UPocketWorldsUIWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}