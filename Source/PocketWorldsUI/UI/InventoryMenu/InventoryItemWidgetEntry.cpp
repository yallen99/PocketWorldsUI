// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemWidgetEntry.h"

#include "CommonLazyImage.h"
#include "CommonTextBlock.h"

void UInventoryItemWidgetEntry::SetItemData(const FText& ItemName, const TSoftObjectPtr<UTexture2D>& Icon)
{
	SetItemName(ItemName);
	SetItemIcon(Icon);
}

void UInventoryItemWidgetEntry::SetItemName(const FText& ItemName)
{
	if (IsValid(ItemNameText))
	{
		ItemNameText->SetText(ItemName);
	}
}

void UInventoryItemWidgetEntry::SetItemIcon(const TSoftObjectPtr<UTexture2D>& Icon)
{
	if (IsValid(ItemIcon))
	{
		ItemIcon->SetBrushFromLazyTexture(Icon);
	}
}
