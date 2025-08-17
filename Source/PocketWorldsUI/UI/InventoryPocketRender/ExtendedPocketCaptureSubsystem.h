// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PocketCaptureSubsystem.h"

#include "ExtendedPocketCaptureSubsystem.generated.h"

class UExtendedPocketCapture;
/**
 * This is an extension of the Pocket capture subsystem provided by the plugin.
 * It allows us to track the captures that we created.
 */
UCLASS()
class POCKETWORLDSUI_API UExtendedPocketCaptureSubsystem : public UPocketCaptureSubsystem
{
	GENERATED_BODY()
public:
	TWeakObjectPtr<UExtendedPocketCapture> GetRendererForId(const FName& RendererName);
	void TrackNewCapture(const TWeakObjectPtr<UExtendedPocketCapture>& Capture);

protected:
	TArray<TWeakObjectPtr<UExtendedPocketCapture>> TrackedRenderers;
};
