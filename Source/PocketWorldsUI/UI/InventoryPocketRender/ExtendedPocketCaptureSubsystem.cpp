// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedPocketCaptureSubsystem.h"

#include "ExtendedPocketCapture.h"

TWeakObjectPtr<UExtendedPocketCapture> UExtendedPocketCaptureSubsystem::GetRendererForId(const FName& RendererName)
{
	const TWeakObjectPtr<UExtendedPocketCapture>* FoundRenderer = TrackedRenderers.FindByPredicate([RendererName] (const TWeakObjectPtr<UExtendedPocketCapture>& Other)
	{
		return Other->GetPocketCaptureName() == RendererName;
	});
	if (FoundRenderer)
	{
		return *FoundRenderer;
	}
	return nullptr;
}

void UExtendedPocketCaptureSubsystem::TrackNewCapture(const TWeakObjectPtr<UExtendedPocketCapture>& Capture)
{
	TrackedRenderers.Add(Capture);
}
