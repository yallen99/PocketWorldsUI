// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UIDevSettings.generated.h"

class UInputMappingContext;
/**
 * Developer settings class that allows us to expose static UI properties to the Project Settings in editor
 */
class UUILayoutWidget;

UCLASS(Config=Game)
class POCKETWORLDSUI_API UUIDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UUIDevSettings* Get()
	{
		return GetDefault<UUIDevSettings>();
	}

	static const TSoftClassPtr<UUILayoutWidget>& GetUILayoutWidget() { return Get()->UILayout; }

private:
	UPROPERTY(Config, EditDefaultsOnly, Category = "Core UI Settings", meta=(Tooltip = "Layout widget containing stacks to which we can push layers"))
	TSoftClassPtr<UUILayoutWidget> UILayout = nullptr;
};
