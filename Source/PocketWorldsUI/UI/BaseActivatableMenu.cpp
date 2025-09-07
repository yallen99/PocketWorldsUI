// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActivatableMenu.h"

#include "UIManagerSubsystem.h"

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

bool UBaseActivatableMenu::NativeOnHandleBackAction()
{
	UUIManagerSubsystem::CloseMenu(this, *this);
	return Super::NativeOnHandleBackAction();
}
