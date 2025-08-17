// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PocketCapture.h"

#include "ExtendedPocketCapture.generated.h"

/**
 * Extension from UPocketCapture to add the name identifier
 */
UCLASS(Abstract, Within=PocketCaptureSubsystem, BlueprintType, Blueprintable)
class POCKETWORLDSUI_API UExtendedPocketCapture : public UPocketCapture
{
	GENERATED_BODY()
public:
	FName GetPocketCaptureName() const { return PocketCaptureName; }

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName PocketCaptureName;

};
