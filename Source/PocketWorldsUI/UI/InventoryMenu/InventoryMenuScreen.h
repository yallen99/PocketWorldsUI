// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "InventoryMenuScreen.generated.h"

struct FGameplayTag;

UENUM()
enum class EScreenInputMode: uint8
{
	GameAndMenu,
	Game,
	Menu
};

class UCommonLazyImage;
class UCommonTileView;
class UMaterialInterface;

UCLASS(Abstract)
class POCKETWORLDSUI_API UInventoryMenuScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

private:
	void SetItemsInGrid();
	void SetCapturePreview();

	void OnGridItemSelectionChanged(UObject* SelectedItem);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTileView> InventoryGrid = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> ItemPreviewImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Pocket Capture")
	FGameplayTag PocketCaptureId = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EScreenInputMode InputConfig = EScreenInputMode::Game;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
};