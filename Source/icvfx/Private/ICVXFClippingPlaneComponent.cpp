// Fill out your copyright notice in the Description page of Project Settings.


#include "ICVXFClippingPlaneComponent.h"

#include "Components/SceneCaptureComponent2D.h"

#include "CineCameraComponent.h"
#include "CineCameraActor.h"


UICVXFClippingPlaneComponent::UICVXFClippingPlaneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}


void UICVXFClippingPlaneComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!bEnabled)
	{
		return;
	}

	// Make sure all the required components exist

	const auto ScreenTransform = Cast<USceneComponent>(ScreenComponentRef.GetComponent(nullptr));

	USceneCaptureComponent2D* SceneCaptureComponent = nullptr;
	if (SceneCaptureActor)
	{
		SceneCaptureComponent = Cast<USceneCaptureComponent2D>(SceneCaptureActor->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
	}

	UCineCameraComponent* CineCameraComponent = nullptr;
	if (CineCameraActor)
	{
		CineCameraComponent = Cast<UCineCameraComponent>(CineCameraActor->GetComponentByClass(UCineCameraComponent::StaticClass()));
	}

	if (!SceneCaptureComponent || !ScreenTransform || !CineCameraComponent)
	{
		// Disable all clipping
		if (SceneCaptureComponent) SceneCaptureComponent->bEnableClipPlane = false;
		if (CineCameraComponent) CineCameraComponent->bOverride_CustomNearClippingPlane = false;

		bIsSetUpCorrect = false;
		return;
	}

	bIsSetUpCorrect = true;

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

void UICVXFClippingPlaneComponent::DebugCheckSetup() const
{
	const bool SceneComponentValid = ScreenComponentRef.GetComponent(nullptr) != nullptr;
	const bool ScreenCaptureComponentValid = SceneCaptureActor->GetComponentByClass(USceneCaptureComponent2D::StaticClass()) != nullptr;
	const bool CineCameraComponentValid = CineCameraActor->GetComponentByClass(UCineCameraComponent::StaticClass()) != nullptr;

	FString DebugString = FString::Printf(
		TEXT("Is set up correct: %d\n SceneComponent: %d\n ScreenCaptureComponent: %d\n CineCameraComponent: %d"),
		bIsSetUpCorrect, SceneComponentValid, ScreenCaptureComponentValid, CineCameraComponentValid
	);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, DebugString);
}
