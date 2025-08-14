// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryMenuScreen.generated.h"

UENUM()
enum class EScreenInputMode: uint8
{
	GameAndMenu,
	Game,
	Menu
};

class UCommonLazyImage;
class UCommonTileView;

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
	void UpdatePreview();

	void OnGridItemSelectionChanged(UObject* SelectedItem);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTileView> InventoryGrid = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> ItemPreviewImage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EScreenInputMode InputConfig = EScreenInputMode::Game;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
};