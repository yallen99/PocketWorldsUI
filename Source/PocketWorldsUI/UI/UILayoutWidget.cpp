// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayoutWidget.h"

#include "CommonActivatableWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UIDevSettings.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UUILayoutWidget::PushWidgetToStack(const TSubclassOf<UCommonActivatableWidget>& WidgetToAdd)
{
	if(IsValid(MenuStack) && IsValid(WidgetToAdd))
	{
		MenuStack->AddWidget(WidgetToAdd);
	}
}

void UUILayoutWidget::PopWidgetFromStack(UCommonActivatableWidget& WidgetToRemove)
{
	if(IsValid(MenuStack))
	{
		MenuStack->RemoveWidget(WidgetToRemove);
	}
}

void UUILayoutWidget::NativeConstruct()
{
	Super::NativeConstruct();
	AddBaseUIInputMappingContext();
}

void UUILayoutWidget::NativeDestruct()
{
	RemoveBaseUIInputMappingContext();
	Super::NativeDestruct();
}

void UUILayoutWidget::AddBaseUIInputMappingContext()
{
	const TSoftObjectPtr<UInputMappingContext>& UIInputMappingContext = UUIDevSettings::GetUIBaseMappingContext();
	const uint8 UIInputMappingContextPriority = UUIDevSettings::GetUIMappingContextPriority();
	if(UIInputMappingContext.IsNull())
	{
		return;
	}

	// todo - Not ideal to load it sync here, but for now it would do. We need those actions to do anything UI related
	BaseUIMappingContext = UIInputMappingContext.LoadSynchronous();

	if(!IsValid(BaseUIMappingContext))
	{
		return;
	}
	if(UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer()))
	{
		EnhancedInputSubsystem->AddMappingContext(BaseUIMappingContext, UIInputMappingContextPriority);
	}
}

void UUILayoutWidget::RemoveBaseUIInputMappingContext()
{
	if(IsValid(BaseUIMappingContext))
	{
		if(UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer()))
		{
			EnhancedInputSubsystem->RemoveMappingContext(BaseUIMappingContext);
		}
	}
}
