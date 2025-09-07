// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PocketWorldsUI/UI/BaseActivatableMenu.h"
#include "InventoryMenu.generated.h"

class UCommonButtonBase;
class UInventoryItemObject;
struct FGameplayTag;


class UCommonLazyImage;
class UCommonTileView;
class UMaterialInterface;

UCLASS(Abstract)
class POCKETWORLDSUI_API UInventoryMenu : public UBaseActivatableMenu
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

private:
	void SetItemsInGrid();
	void SetCapturePreview();

	void OnGridItemSelectionChanged(UObject* SelectedItem);
	void EquipItem();

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTileView> InventoryGrid = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> ItemPreviewImage = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> EquipButton = nullptr;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UInventoryItemObject>> Items;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pocket Capture")
	FGameplayTag PocketCaptureId = FGameplayTag::EmptyTag;
};