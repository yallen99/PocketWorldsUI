// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"

#include "UIDevSettings.h"
#include "UILayoutWidget.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UUIManagerSubsystem::OpenMenu(const UObject* ContextObject, const TSubclassOf<UCommonActivatableWidget>& ActivatableMenu)
{
	UUIManagerSubsystem* UIManager = UUIManagerSubsystem::Get(ContextObject);
	if (!IsValid(UIManager) || !IsValid(UIManager->LayoutWidget))
	{
		return;
	}
	UIManager->LayoutWidget->PushWidgetToStack(ActivatableMenu);
}

void UUIManagerSubsystem::CloseMenu(const UObject* ContextObject, UCommonActivatableWidget& ActivatableMenu)
{
	UUIManagerSubsystem* UIManager = UUIManagerSubsystem::Get(ContextObject);
	if (!IsValid(UIManager) || !IsValid(UIManager->LayoutWidget))
	{
		return;
	}
	UIManager->LayoutWidget->PopWidgetFromStack(ActivatableMenu);
}

UUIManagerSubsystem* UUIManagerSubsystem::Get(const UObject* ContextObject)
{
	if(!IsValid(ContextObject))
	{
		return nullptr;
	}
	UWorld* World = ContextObject->GetWorld();
	if(!IsValid(World) || World->bIsTearingDown)
	{
		return nullptr;
	}
	return World->GetSubsystem<UUIManagerSubsystem>();
}

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (!GetWorld()->IsGameWorld())
	{
		return;
	}
	CreateUILayout();
}

void UUIManagerSubsystem::Deinitialize()
{
	if (GetWorld()->IsGameWorld())
	{
		DestroyUILayout();
	}
	Super::Deinitialize();
}

void UUIManagerSubsystem::CreateUILayout()
{
	const TSoftClassPtr<UUILayoutWidget>& SoftUILayout = UUIDevSettings::GetUILayoutWidget();
	if(SoftUILayout.IsNull())
	{
		return;
	}
	
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(SoftUILayout.ToSoftObjectPath(),
		FSimpleDelegate::CreateUObject(this, &ThisClass::OnLayoutAssetLoaded));
} 

void UUIManagerSubsystem::DestroyUILayout()
{
	if(IsValid(LayoutWidget))
	{
		LayoutWidget->Destruct();
	}
	LayoutWidget = nullptr;
}

void UUIManagerSubsystem::OnLayoutAssetLoaded()
{
	const TSoftClassPtr<UUILayoutWidget>& SoftUILayout = UUIDevSettings::GetUILayoutWidget();
	UClass* LayoutClass = SoftUILayout.Get();
	LayoutWidget = CreateWidget<UUILayoutWidget>(GetWorld(), LayoutClass);
	if(IsValid(LayoutWidget))
	{
		LayoutWidget->AddToViewport();
	}
}
