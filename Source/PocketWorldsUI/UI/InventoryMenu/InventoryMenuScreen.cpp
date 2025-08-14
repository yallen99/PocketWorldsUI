// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuScreen.h"

#include "CommonTileView.h"
#include "InventoryItemObject.h"

void UInventoryMenuScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	// Bind even to the grid selection changed so we can update the preview
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnGridItemSelectionChanged);
	}
}

void UInventoryMenuScreen::NativeOnDeactivated()
{
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->OnItemSelectionChanged().RemoveAll(this);
	}
	Super::NativeOnDeactivated();
}

void UInventoryMenuScreen::SetItemsInGrid()
{
}

void UInventoryMenuScreen::UpdatePreview()
{
}

void UInventoryMenuScreen::OnGridItemSelectionChanged(UObject* SelectedItem)
{
	if (UInventoryItemObject* InventoryItem = Cast<UInventoryItemObject>(SelectedItem))
	{
		// Do something with the item?
	}
}
