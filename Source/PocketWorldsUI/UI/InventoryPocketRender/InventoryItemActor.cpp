// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemActor.h"

#include "Camera/CameraComponent.h"
#include "PocketCapture.h"
#include "PocketCaptureSubsystem.h"

AInventoryItemActor::AInventoryItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetMobility(EComponentMobility::Type::Static);

	// Initialize camera component. This is crucial for the render capture.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootSceneComponent);
	CameraComponent->SetRelativeLocation(CameraLocation);
	CameraComponent->SetRelativeRotation(CameraRotation);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->SetAspectRatio(AspectRatio);
}

void AInventoryItemActor::BeginPlay()
{
	Super::BeginPlay();
	UPocketCaptureSubsystem* PocketCaptureSubsystem = GetWorld()->GetSubsystem<UPocketCaptureSubsystem>();
	PocketCapturePtr = PocketCaptureSubsystem->CreateThumbnailRenderer(PocketCaptureClass);
	PocketCapturePtr->SetRenderTargetSize(RenderTargetSize.X, RenderTargetSize.Y);
	PocketCapturePtr->SetCaptureTarget(this);
}
