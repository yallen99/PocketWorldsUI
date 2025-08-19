// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActivatableMenu.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"

#include "UILayoutWidget.generated.h"

class UBaseActivatableMenu;
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

	// Get the currently active widget on this stack, or nullptr if the stack is empty
	UBaseActivatableMenu* GetTopOfTheStack();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void AddBaseUIInputMappingContext();
	void RemoveBaseUIInputMappingContext();

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UInputMappingContext> BaseUIMappingContext = nullptr;
};
