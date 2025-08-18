// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenuScreen.h"

#include "CommonLazyImage.h"
#include "CommonTileView.h"
#include "InventoryItemObject.h"
#include "PocketCapture.h"
#include "PocketCaptureSubsystem.h"
#include "Data/InventoryItemsData.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PocketWorldsUI/UI/UIDevSettings.h"
#include "PocketWorldsUI/UI/UIManagerSubsystem.h"

void UInventoryMenuScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	// Bind even to the grid selection changed so we can update the preview
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->OnItemSelectionChanged().AddUObject(this, &ThisClass::OnGridItemSelectionChanged);
	}

	// Temporary solution for setting the items in grid. This data already exists in the inventory component.
	// We should grab it from there
	SetItemsInGrid();
}

void UInventoryMenuScreen::NativeOnDeactivated()
{
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->OnItemSelectionChanged().RemoveAll(this);
	}
	UUIManagerSubsystem::CloseMenu(this, *this);
	Super::NativeOnDeactivated();
}

// todo - from Lyra @ EPIC - this belongs in a base class for screens
TOptional<FUIInputConfig> UInventoryMenuScreen::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case EScreenInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case EScreenInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case EScreenInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	default: return TOptional<FUIInputConfig>();
	}
}

void UInventoryMenuScreen::SetItemsInGrid()
{
	const TSoftObjectPtr<UInventoryItemsData>& SoftInventoryTablePtr = UUIDevSettings::GetInventoryData();
	const UInventoryItemsData* LoadedStaticInventoryAsset = SoftInventoryTablePtr.LoadSynchronous();
	TArray<UInventoryItemObject*> Items;
	if(IsValid(LoadedStaticInventoryAsset))
	{
		for (const TPair<FGameplayTag, FInventoryItemData>& Item : LoadedStaticInventoryAsset->ItemData)
		{
			UInventoryItemObject* NewInventoryItem = NewObject<UInventoryItemObject>();
			NewInventoryItem->ItemData = Item.Value;
			Items.Add(NewInventoryItem);
		}
	}
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->SetListItems(Items);
	}

	// todo - this would have to be updated when the grid selection changes. For now, set it here
	SetCapturePreview();
}

void UInventoryMenuScreen::SetCapturePreview()
{
	UPocketCaptureSubsystem* PocketCaptureSubsystem = GetWorld()->GetSubsystem<UPocketCaptureSubsystem>();
	UPocketCapture* PocketCapture = PocketCaptureSubsystem->GetRendererForId(PocketCaptureId).Get();
	if (IsValid(ItemPreviewImage) && IsValid(PocketCapture))
	{
		UMaterialInstanceDynamic* RenderMaterialInst = ItemPreviewImage->GetDynamicMaterial();
		if (IsValid(RenderMaterialInst))
		{
			PocketCapture->CaptureDiffuse();
			PocketCapture->CaptureAlphaMask();
			RenderMaterialInst->SetTextureParameterValue(TEXT("Diffuse"), PocketCapture->GetOrCreateDiffuseRenderTarget());
			RenderMaterialInst->SetTextureParameterValue(TEXT("AlphaMask"), PocketCapture->GetOrCreateAlphaMaskRenderTarget());
		}
	}
}

void UInventoryMenuScreen::OnGridItemSelectionChanged(UObject* SelectedItem)
{
	if (UInventoryItemObject* InventoryItem = Cast<UInventoryItemObject>(SelectedItem))
	{
		// Do something with the item?
	}
}
