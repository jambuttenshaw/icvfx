// Fill out your copyright notice in the Description page of Project Settings.


#include "CompClippingPlaneComponent.h"

#include "Components/SceneCaptureComponent2D.h"


UCompClippingPlaneComponent::UCompClippingPlaneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Allow component to tick in editor to allow the clipping plane to always be adjusted
	bTickInEditor = true;

	FindSceneCaptureComponent();
}


void UCompClippingPlaneComponent::BeginPlay()
{
	Super::BeginPlay();

	FindSceneCaptureComponent();
}


void UCompClippingPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Must have both a scene capture component and a screen to align the plane with
	auto ScreenComponent = StaticCast<USceneComponent*>(ScreenComponentRef.GetComponent(nullptr));
	if (!SceneCaptureComponent || !ScreenComponent)
	{
		SceneCaptureComponent->bEnableClipPlane = false;
		return;
	}

	// Update the clipping plane

	// The clipping plane is specified in world-space
	// Get world-space normal of the screen
	const FVector PlaneNormal = ScreenComponent->GetForwardVector() * (bClipForeground ? 1 : -1);
	const FVector PlaneBase = ScreenComponent->GetComponentLocation();

	SceneCaptureComponent->bEnableClipPlane = true;

	SceneCaptureComponent->ClipPlaneNormal = PlaneNormal;
	SceneCaptureComponent->ClipPlaneBase = PlaneBase;
}


void UCompClippingPlaneComponent::FindSceneCaptureComponent()
{
	if (SceneCaptureComponent)
	{
		return;
	}

	if (const AActor* Owner = GetOwner())
	{
		SceneCaptureComponent = StaticCast<USceneCaptureComponent2D*>(Owner->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	}
}
