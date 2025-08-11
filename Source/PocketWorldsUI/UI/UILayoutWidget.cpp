// Fill out your copyright notice in the Description page of Project Settings.


#include "UILayoutWidget.h"

#include "CommonActivatableWidget.h"
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
}
