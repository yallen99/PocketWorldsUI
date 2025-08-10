// Copyright Epic Games, Inc. All Rights Reserved.

#include "PocketWorldsUIGameMode.h"
#include "PocketWorldsUIPlayerController.h"

APocketWorldsUIGameMode::APocketWorldsUIGameMode()
{
	PlayerControllerClass = APocketWorldsUIPlayerController::StaticClass();
}
