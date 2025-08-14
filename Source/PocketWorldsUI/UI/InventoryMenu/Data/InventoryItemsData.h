// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PocketWorldsUI/UI/InventoryMenu/InventoryItemObject.h"
#include "InventoryItemsData.generated.h"

/**
 * Normally the data for an inventory would be provided on the fly by some game system. In this case,
 * the data is static, defined in this data asset
 */
UCLASS()
class POCKETWORLDSUI_API UInventoryItemsData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FInventoryItemData> ItemData;
};
