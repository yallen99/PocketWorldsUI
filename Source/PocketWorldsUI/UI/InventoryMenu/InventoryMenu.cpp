// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenu.h"

#include "CommonButtonBase.h"
#include "CommonLazyImage.h"
#include "CommonTileView.h"
#include "InventoryItemObject.h"
#include "PocketCapture.h"
#include "PocketCaptureSubsystem.h"
#include "Data/InventoryItemsData.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "PocketWorldsUI/UI/UIDevSettings.h"
#include "PocketWorldsUI/UI/UINativeGameplayTags.h"

void UInventoryMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(EquipButton))
	{
		EquipButton->OnClicked().AddUObject(this, &ThisClass::EquipItem);
	}
}

void UInventoryMenu::NativeDestruct()
{
	if (IsValid(EquipButton))
	{
		EquipButton->OnClicked().RemoveAll(this);
	}
	Super::NativeDestruct();
}

void UInventoryMenu::NativeOnActivated()
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

void UInventoryMenu::NativeOnDeactivated()
{
	if (IsValid(InventoryGrid))
	{
		InventoryGrid->OnItemSelectionChanged().RemoveAll(this);
	}
	Super::NativeOnDeactivated();
}

void UInventoryMenu::SetItemsInGrid()
{
	if (!IsValid(InventoryGrid))
	{
		return;
	}
	const TSoftObjectPtr<UInventoryItemsData>& SoftInventoryTablePtr = UUIDevSettings::GetInventoryData();
	const UInventoryItemsData* LoadedStaticInventoryAsset = SoftInventoryTablePtr.LoadSynchronous();

	Items.Empty();
	if(IsValid(LoadedStaticInventoryAsset))
	{
		for (const TPair<FGameplayTag, FInventoryItemData>& Item : LoadedStaticInventoryAsset->ItemData)
		{
			UInventoryItemObject* NewInventoryItem = NewObject<UInventoryItemObject>();
			NewInventoryItem->ItemData = Item.Value;
			Items.Add(NewInventoryItem);
		}
	}
	
	InventoryGrid->SetListItems(Items);
	InventoryGrid->SetSelectedIndex(0);
	SetCapturePreview();
}

void UInventoryMenu::SetCapturePreview()
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

void UInventoryMenu::OnGridItemSelectionChanged(UObject* SelectedItem)
{
	if (UInventoryItemObject* InventoryItem = Cast<UInventoryItemObject>(SelectedItem))
	{
		FGameplayTag& SelectedTag = InventoryItem->ItemData.ItemId;
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.BroadcastMessage(UI_Inventory_Events_OnItemSelectionChanged, SelectedTag);
		SetCapturePreview();
	}
}

void UInventoryMenu::EquipItem()
{
	if (!IsValid(InventoryGrid))
	{
		return;
	}
	if (const UInventoryItemObject* SelectedItem = InventoryGrid->GetSelectedItem<UInventoryItemObject>())
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.BroadcastMessage(UI_Inventory_Events_OnItemEquipped, SelectedItem->ItemData.ItemId);
	}
	HandleBackAction();
}
