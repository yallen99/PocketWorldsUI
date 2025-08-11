// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UCommonActivatableWidget;
class UUILayoutWidget;
/**
 * UI Manager subsystem (world subsystem) manages the UI Layout and allows us to Push & Pop menus to the screen
 */
UCLASS()
class POCKETWORLDSUI_API UUIManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	static UUIManagerSubsystem* Get(const UObject* ContextObject);
	static void OpenMenu(const UObject* ContextObject, const TSubclassOf<UCommonActivatableWidget>& ActivatableMenu);
	static void CloseMenu(const UObject* ContextObject, UCommonActivatableWidget& ActivatableMenu);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void CreateUILayout();
	void DestroyUILayout();

	void OnLayoutAssetLoaded();
	UPROPERTY(Transient)
	TObjectPtr<UUILayoutWidget> LayoutWidget = nullptr;
};
