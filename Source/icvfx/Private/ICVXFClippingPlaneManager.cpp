// Fill out your copyright notice in the Description page of Project Settings.


#include "ICVXFClippingPlaneManager.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Runtime/CinematicCamera/Public/CineCameraComponent.h"

UICVXFClippingPlaneManager::UICVXFClippingPlaneManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}


void UICVXFClippingPlaneManager::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Make sure all the required components exist

	const auto ScreenTransform = Cast<USceneComponent>(ScreenComponentRef.GetComponent(nullptr));

	USceneCaptureComponent2D* SceneCaptureComponent = nullptr;
	if (AActor* Actor = SceneCaptureComponentRef.OtherActor.Get())
	{
		SceneCaptureComponent = Cast<USceneCaptureComponent2D>(Actor->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	}

	//const auto SceneCaptureComponent = StaticCast<USceneCaptureComponent2D*>(SceneCaptureComponentRef.GetComponent(nullptr));
	const auto CineCameraComponent = Cast<UCineCameraComponent>(CineCameraComponentRef.GetComponent(nullptr));

	if (!SceneCaptureComponent || !ScreenTransform || !CineCameraComponent)
	{
		// Disable all clipping
		if (SceneCaptureComponent) SceneCaptureComponent->bEnableClipPlane = false;
		if (CineCameraComponent) CineCameraComponent->bOverride_CustomNearClippingPlane = false;

		return;
	}

	// Set up clipping planes
	// Get the normal and position on plane
	const FVector PlaneNormal = ScreenTransform->GetForwardVector() * (bFlipClippingPlane ? -1 : 1);
	const FVector PlanePosition = ScreenTransform->GetComponentLocation();

	{
		// Set up scene capture component
		SceneCaptureComponent->bEnableClipPlane = true;

		SceneCaptureComponent->ClipPlaneNormal = PlaneNormal;
		SceneCaptureComponent->ClipPlaneBase = PlanePosition;
	}

	{
		// Set up custom near plane distance for CineCamera
		// This will be less effective at oblique angles to the frustum,
		// but in general that is not too likely/common in a VP setting

		// CineCameras (and Camera's in general) do not allow for manipulation of the global clip plane unfortunately

		const FVector CineCameraLocation = CineCameraComponent->GetComponentLocation();

		const float DistanceToPlane = FMath::Abs(
			FVector::DotProduct(PlaneNormal, CineCameraLocation) - FVector::DotProduct(PlaneNormal, PlanePosition)
		);

		CineCameraComponent->bOverride_CustomNearClippingPlane = true;
		CineCameraComponent->CustomNearClippingPlane = DistanceToPlane;
	}
}
