// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "EnhancedInputSubsystems.h"
#include "PocketLevelInstance.h"
#include "PocketLevelSystem.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "PocketWorldsUI/UI/UIDevSettings.h"
#include "PocketWorldsUI/UI/UIManagerSubsystem.h"
#include "PocketWorldsUI/UI/InventoryMenu/Data/InventoryItemsData.h"
#include "PocketWorldsUI/UI/InventoryMenu/InventoryMenu.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	AttachInventoryMappingContext();
	PopulateStaticInventory();
	SpawnInventoryPreviewLevel();
}

void UInventoryComponent::OpenUIInventory()
{
	if (IsValid(InventoryLevel))
	{
		// Stream in the level
		InventoryLevel->StreamIn();
		// When the level is ready, open the screen
		InventoryLevel->AddReadyCallback(FPocketLevelInstanceEvent::FDelegate::CreateUObject(this, &ThisClass::OpenUIInventoryMenu));
	}
}

void UInventoryComponent::OpenUIInventoryMenu(UPocketLevelInstance* PocketLevelInstance) const
{
	UUIManagerSubsystem::OpenMenu(this, InventoryMenuSubclass);
}

void UInventoryComponent::OnInventoryAssetLoaded()
{
	// We don't need to do anything with the inventory here (not for now, or for this example)
	// We only need the inventory asset to be added for UI display purposes.
}

void UInventoryComponent::PopulateStaticInventory()
{
	const TSoftObjectPtr<UInventoryItemsData>& SoftInventoryTablePtr = UUIDevSettings::GetInventoryData();
	if (SoftInventoryTablePtr.IsNull())
	{
		return;
	}
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(SoftInventoryTablePtr.ToSoftObjectPath(),
		FSimpleDelegate::CreateUObject(this, &ThisClass::OnInventoryAssetLoaded));
}

void UInventoryComponent::AttachInventoryMappingContext()
{
	const UWorld* World = GetWorld();
	if (!IsValid(World) || World->bIsTearingDown)
	{
		return;
	}
	const APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		return;
	}
	
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(FirstPlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InventoryActions, 0);
	}
}

void UInventoryComponent::SpawnInventoryPreviewLevel()
{
	if (const UWorld* World = GetWorld())
	{
		if (UPocketLevelSubsystem* PocketLevelSubsystem = World->GetSubsystem<UPocketLevelSubsystem>())
		{
			InventoryLevel = PocketLevelSubsystem->GetOrCreatePocketLevelFor(World->GetFirstLocalPlayerFromController(), PocketLevelDefinition, PocketLevelSpawnLocation);
			InventoryLevel->StreamOut();		// temporarily disable/stream out the level until we need it.
		}
	}
}


