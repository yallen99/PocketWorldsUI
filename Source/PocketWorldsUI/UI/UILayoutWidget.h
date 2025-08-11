// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"

#include "UILayoutWidget.generated.h"

class UCommonActivatableWidgetStack;

/**
 * Widget containing the stacks that will handle different layers of the UI, such as HUD or fullscreen menus
 */
UCLASS()
class POCKETWORLDSUI_API UUILayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	void PushWidgetToStack(const TSubclassOf<UCommonActivatableWidget>& WidgetToAdd);
	void PopWidgetFromStack(UCommonActivatableWidget& WidgetToRemove);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack = nullptr;
};
