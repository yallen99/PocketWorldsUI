// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseActivatableMenu.generated.h"

/**
 * This class is meant to be the parent of any menu that we want to push or pop from the layer(s) on the layout.
 * It offers functionality that handles the input mode, back actions, and more root functions
 */
UCLASS(Abstract)
class POCKETWORLDSUI_API UBaseActivatableMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	virtual bool NativeOnHandleBackAction() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	ECommonInputMode InputConfig = ECommonInputMode::Game;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
};
