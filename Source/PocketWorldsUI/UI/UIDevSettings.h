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
	static const TSoftObjectPtr<UInputMappingContext>& GetUIBaseMappingContext() { return Get()->UIBaseInputMappingContext; }
	static uint8 GetUIMappingContextPriority() { return Get()->BaseMappingContextPriority; }

private:
	UPROPERTY(Config, EditDefaultsOnly, Category = "Core UI Settings|Input")
	TSoftObjectPtr<UInputMappingContext> UIBaseInputMappingContext;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Core UI Settings|Input", meta=(Tooltip = "Priority for the IMC UI Base actions. This is usually higher than the gameplay inputs"))
	uint8 BaseMappingContextPriority = 10;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Core UI Settings", meta=(Tooltip = "Layout widget containing stacks to which we can push layers"))
	TSoftClassPtr<UUILayoutWidget> UILayout = nullptr;
};
