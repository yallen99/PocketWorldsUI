// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"

#include "PocketCapture.generated.h"

struct FGameplayTag;
enum ESceneCaptureSource : int;

class UMaterialInterface;
class UPocketCaptureSubsystem;
class UPrimitiveComponent;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
class UWorld;
struct FFrame;

UCLASS(Abstract, Within=PocketCaptureSubsystem, BlueprintType, Blueprintable)
class POCKETWORLDS_API UPocketCapture : public UObject
{
	GENERATED_BODY()

public:
	UPocketCapture();

	virtual void Initialize(UWorld* InWorld, int32 RendererIndex);
	virtual void Deinitialize();

	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable)
	void SetRenderTargetSize(int32 Width, int32 Height);

	UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetOrCreateDiffuseRenderTarget();

	UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetOrCreateAlphaMaskRenderTarget();

	UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetOrCreateEffectsRenderTarget();

	UFUNCTION(BlueprintCallable)
	const FGameplayTag& GetCaptureId() const;

	UFUNCTION(BlueprintCallable)
	void SetCaptureTarget(AActor* InCaptureTarget);

	UFUNCTION(BlueprintCallable)
	void SetAlphaMaskedActors(const TArray<AActor*>& InCaptureTarget);

	UFUNCTION(BlueprintCallable)
	void CaptureDiffuse();

	UFUNCTION(BlueprintCallable)
	void CaptureAlphaMask();

	UFUNCTION(BlueprintCallable)
	void CaptureEffects();

	UFUNCTION(BlueprintCallable)
	virtual void ReleaseResources();

	UFUNCTION(BlueprintCallable)
	virtual void ReclaimResources();

	UFUNCTION(BlueprintCallable)
	int32 GetRendererIndex() const;
	
protected:
	AActor* GetCaptureTarget() const { return CaptureTargetPtr.Get(); }
	virtual void OnCaptureTargetChanged(AActor* InCaptureTarget) {}

	bool CaptureScene(UTextureRenderTarget2D* InRenderTarget, const TArray<AActor*>& InCaptureActors, ESceneCaptureSource CaptureSource, UMaterialInterface* OverrideMaterial);

	TArray<UPrimitiveComponent*> GatherPrimitivesForCapture(const TArray<AActor*>& InCaptureActors) const;
	
	UPocketCaptureSubsystem* GetThumbnailSystem() const;
	
	UPROPERTY(EditDefaultsOnly, Category= "Materials")
	TObjectPtr<UMaterialInterface> AlphaMaskMaterial;

	UPROPERTY(EditDefaultsOnly, Category= "Materials")
	TObjectPtr<UMaterialInterface> EffectMaskMaterial;

	UPROPERTY(Transient)
	TObjectPtr<UWorld> PrivateWorld;

	UPROPERTY(Transient)
	int32 RendererIndex = INDEX_NONE;

	UPROPERTY(Transient)
	TObjectPtr<USceneCaptureComponent2D> CaptureComponent;

	UPROPERTY(EditDefaultsOnly, meta=(Categories=PocketCapture, ToolTip="Render Target Id. Must be a tag that starts with `PocketCapture.`"))
	FGameplayTag CaptureId = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, Category="Render Target Properties")
	int32 SurfaceWidth = 1;

	UPROPERTY(EditDefaultsOnly, Category="Render Target Properties")
	int32 SurfaceHeight = 1;

	UPROPERTY(EditDefaultsOnly, Category="Render Target Properties")
	TObjectPtr<UTextureRenderTarget2D> DiffuseRT;

	UPROPERTY(EditDefaultsOnly, Category="Render Target Properties")
	TObjectPtr<UTextureRenderTarget2D> AlphaMaskRT;

	UPROPERTY(EditDefaultsOnly, Category="Render Target Properties")
	TObjectPtr<UTextureRenderTarget2D> EffectsRT;

	UPROPERTY(EditDefaultsOnly, Category="Captures")
	TWeakObjectPtr<AActor> CaptureTargetPtr;

	UPROPERTY(EditDefaultsOnly, Category="Captures")
	TArray<TWeakObjectPtr<AActor>> AlphaMaskActorPtrs;
};
