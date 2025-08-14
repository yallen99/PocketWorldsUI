// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "InventoryItemObject.generated.h"

/**
 * Struct used to define the UI data for an inventory item. Used for static definitions and grid population
 */
USTRUCT(BlueprintType)
struct FInventoryItemData
{
	GENERATED_BODY()
	FInventoryItemData() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditAnywhere)
	FText ItemName = FText::GetEmpty();

	UPROPERTY(EditAnywhere)
	FGameplayTag ItemId = FGameplayTag::EmptyTag;
};

/**
 * Source object used to populate the inventory grid with
 */
UCLASS()
class POCKETWORLDSUI_API UInventoryItemObject : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	FInventoryItemData ItemData;
};
