// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "InventoryItemActor.generated.h"

class UInventoryItemObject;
struct FGameplayTag;

class UCameraComponent;
class UPocketCapture;

/// Actor used to capture in the pocket world
/// The camera will point at this actor and capture it, then pass it to the render target texture. \n
/// This entire class can be done in blueprints,
/// but for diff purposes, I created the properties in C++ to outline what settings are important
UCLASS()
class POCKETWORLDSUI_API AInventoryItemActor : public AActor
{
	GENERATED_BODY()

public:
	AInventoryItemActor();

protected:
	virtual void BeginPlay() override;

private:
	void SetActiveMeshForId(const FGameplayTag& MeshId);
	void OnInventoryItemSelectionChanged(FGameplayTag Channel, const FGameplayTag& Payload);

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	FVector CameraLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	FRotator CameraRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float FOV = 20.0f;

	UPROPERTY(EditAnywhere, Category="Camera Properties")
	float AspectRatio = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category="Pocket Worlds RT Properties")
	TSubclassOf<UPocketCapture> PocketCaptureClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pocket Worlds RT Properties")
	FVector2D RenderTargetSize = FVector2D(1028, 1028);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> PreviewableActorMeshComponent = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UPocketCapture> PocketCapturePtr = nullptr;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TObjectPtr<USkeletalMesh>> PreviwableActorMeshMap;

	FGameplayMessageListenerHandle OnInventoryItemSelectionChangedHandle;
};
