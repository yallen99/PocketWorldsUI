// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PocketCapture.h"
#include "Components/ActorComponent.h"
#include "PocketWorldsUI/UI/InventoryPocketRender/ExtendedPocketCapture.h"
#include "InventoryComponent.generated.h"

class UExtendedPocketCapture;
class UPocketCapture;
class UPocketLevelInstance;
class UPocketLevel;
class UInventoryMenuScreen;
class UInputMappingContext;
class UInventoryItemObject;

/// This component allows the local player to open the inventory
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POCKETWORLDSUI_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	// todo - for the simplicity sake, we will reference this component directly from the widget to get the ref to the inventory level
	UPocketCapture* GetInventoryPocketCapture() const { return PocketCapturePtr; }
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, meta=(ToolTip = "Open the inventory UI. Meant to be bound in BP to the enahnced action we want to open the inventory with."))
	void OpenUIInventory();

private:
	void OnInventoryAssetLoaded();
	void PopulateStaticInventory();
	void AttachInventoryMappingContext();
	void SpawnInventoryPreviewLevel();
	void OpenUIInventoryMenu(UPocketLevelInstance* PocketLevelInstance) const;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TObjectPtr<UInputMappingContext> InventoryActions = nullptr;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInventoryMenuScreen> InventoryMenuSubclass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Pocket World")
	TObjectPtr<UPocketLevel> PocketLevelDefinition = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Pocket World")
	FVector3d PocketLevelSpawnLocation = FVector3d::Zero();

	UPROPERTY(Transient)
	TObjectPtr<UExtendedPocketCapture> PocketCapturePtr = nullptr;

	/// Array of items that are retrieved from the static inventory data asset
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInventoryItemObject>> StaticInventory;

	UPROPERTY(Transient)
	TObjectPtr<UPocketLevelInstance> InventoryLevel = nullptr;
};
