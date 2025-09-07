// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayoutWidget.h"

#include "BaseActivatableMenu.h"
#include "CommonActivatableWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UIDevSettings.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Input/CommonUIActionRouterBase.h"
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
	if(IsValid(MenuStack))
	{
		MenuStack->OnDisplayedWidgetChanged().AddUObject(this, &ThisClass::ApplyLeafmostInputConfig);
	}
}

void UUILayoutWidget::NativeDestruct()
{
	RemoveBaseUIInputMappingContext();
	if(IsValid(MenuStack))
	{
		MenuStack->OnDisplayedWidgetChanged().RemoveAll(this);
	}
	Super::NativeDestruct();
}

void UUILayoutWidget::ApplyLeafmostInputConfig(UCommonActivatableWidget* CurrentWidget)
{
	UCommonUIActionRouterBase* ActionRouterBase = UCommonUIActionRouterBase::Get(*this);
	if (const UBaseActivatableMenu* ActiveMenu = Cast<UBaseActivatableMenu>(CurrentWidget))
	{
		const FUIInputConfig& CurrentInputConfig = ActiveMenu->GetDesiredInputConfig().GetValue();
		ActionRouterBase->SetActiveUIInputConfig(CurrentInputConfig);
	}
	else
	{
		const FUIInputConfig& CurrentInputConfig = FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
		ActionRouterBase->SetActiveUIInputConfig(CurrentInputConfig);
	}
}

void UUILayoutWidget::OnDefaultUIMappingContextLoaded()
{
	BaseUIMappingContext = UUIDevSettings::GetUIBaseMappingContext().Get();
	const uint8 UIInputMappingContextPriority = UUIDevSettings::GetUIMappingContextPriority();

	if(!IsValid(BaseUIMappingContext))
	{
		return;
	}
	if(UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningLocalPlayer()))
	{
		EnhancedInputSubsystem->AddMappingContext(BaseUIMappingContext, UIInputMappingContextPriority);
	}
}

void UUILayoutWidget::AddBaseUIInputMappingContext()
{
	const TSoftObjectPtr<UInputMappingContext>& UIInputMappingContext = UUIDevSettings::GetUIBaseMappingContext();
	if(UIInputMappingContext.IsNull())
	{
		return;
	}
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(UIInputMappingContext.ToSoftObjectPath(),
		FSimpleDelegate::CreateUObject(this, &ThisClass::OnDefaultUIMappingContextLoaded));
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
