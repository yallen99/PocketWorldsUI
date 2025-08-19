// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PocketWorldsUI/UI/BaseActivatableMenu.h"
#include "InventoryMenu.generated.h"

struct FGameplayTag;


class UCommonLazyImage;
class UCommonTileView;
class UMaterialInterface;

UCLASS(Abstract)
class POCKETWORLDSUI_API UInventoryMenu : public UBaseActivatableMenu
{
	GENERATED_BODY()

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

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
};