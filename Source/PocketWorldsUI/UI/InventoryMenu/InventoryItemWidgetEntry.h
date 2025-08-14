// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventoryItemWidgetEntry.generated.h"

class UCommonTextBlock;
class UCommonLazyImage;

/**
 * Widget used to populate the inventory grid. HAs to be a button and a User Object List Entry.
 */
UCLASS(Abstract)
class POCKETWORLDSUI_API UInventoryItemWidgetEntry : public UCommonButtonBase, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	void SetItemData(const FText& ItemName, const TSoftObjectPtr<UTexture2D>& Icon);

private:
	void SetItemName(const FText& ItemName);
	void SetItemIcon(const TSoftObjectPtr<UTexture2D>& Icon);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonLazyImage> ItemIcon = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> ItemNameText = nullptr;
};
