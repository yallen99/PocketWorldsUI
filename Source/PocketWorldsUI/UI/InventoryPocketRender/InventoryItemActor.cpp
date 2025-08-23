// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemActor.h"

#include "Camera/CameraComponent.h"
#include "PocketCapture.h"
#include "PocketCaptureSubsystem.h"
#include "PocketWorldsUI/UI/UINativeGameplayTags.h"

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

	PreviewableActorMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PreviewableActorMeshComponent"));
	PreviewableActorMeshComponent->SetupAttachment(RootSceneComponent);
	PreviewableActorMeshComponent->SetEnableGravity(false);
	PreviewableActorMeshComponent->SetSimulatePhysics(false);
	if (!PreviwableActorMeshMap.IsEmpty())
	{
		TArray<TObjectPtr<USkeletalMesh>> Meshes;
		PreviwableActorMeshMap.GenerateValueArray(Meshes);
		PreviewableActorMeshComponent->SetSkeletalMesh(Meshes[0]);
	}
}

void AInventoryItemActor::BeginPlay()
{
	Super::BeginPlay();
	UPocketCaptureSubsystem* PocketCaptureSubsystem = GetWorld()->GetSubsystem<UPocketCaptureSubsystem>();
	PocketCapturePtr = PocketCaptureSubsystem->CreateThumbnailRenderer(PocketCaptureClass);
	PocketCapturePtr->SetRenderTargetSize(RenderTargetSize.X, RenderTargetSize.Y);
	PocketCapturePtr->SetCaptureTarget(this);

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	OnInventoryItemSelectionChangedHandle = MessageSubsystem.RegisterListener(UI_Inventory_Events_OnItemSelectionChanged, this,
		&ThisClass::OnInventoryItemSelectionChanged);
}

void AInventoryItemActor::OnInventoryItemSelectionChanged(FGameplayTag Channel, const FGameplayTag& Payload)
{
	if (Payload != FGameplayTag::EmptyTag)
	{
		SetActiveMeshForId(Payload);
	}
}

void AInventoryItemActor::SetActiveMeshForId(const FGameplayTag& MeshId)
{
	USkeletalMesh* NewMesh = PreviwableActorMeshMap.FindRef(MeshId);
	if (IsValid(NewMesh) && IsValid(PreviewableActorMeshComponent))
	{
		PreviewableActorMeshComponent->SetSkeletalMesh(NewMesh);
	}
}
