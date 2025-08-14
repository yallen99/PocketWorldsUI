// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryMenuScreen.generated.h"

class UCommonLazyImage;
class UCommonTileView;

UCLASS(Abstract)
class POCKETWORLDSUI_API UInventoryMenuScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

private:
	void SetItemsInGrid();
	void UpdatePreview();

	void OnGridItemSelectionChanged(UObject* SelectedItem);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTileView> InventoryGrid = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> ItemPreviewImage = nullptr;
};