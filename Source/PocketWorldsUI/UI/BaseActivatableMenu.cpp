// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActivatableMenu.h"

TOptional<FUIInputConfig> UBaseActivatableMenu::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
		case ECommonInputMode::All:
			return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		case ECommonInputMode::Game:
			return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		case ECommonInputMode::Menu:
			return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		default: return Super::GetDesiredInputConfig();
	}
}
