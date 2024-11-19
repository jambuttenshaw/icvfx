// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ICVXFClippingPlaneComponent.generated.h"


class ACineCameraActor;

/*
 * A simple actor component to manage clipping planes for Composure layers and ICVFX rendering
 * It will align a clipping plane for a scene capture component with a nDisplay screen
 * and also set the near clipping distance for the active CineCamera
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ICVFX_API UICVXFClippingPlaneComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UICVXFClippingPlaneComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Blueprint Interface

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSetupCorrect() const { return bIsSetUpCorrect; }

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Debug")
	void DebugCheckSetup() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = true;

	// The screen to align the clipping plane with.
	// Specify a scene component in the editor, usually the nDisplay Screen/Static Mesh used for displaying the backplate
	// The transform of this component will be used to determine the alignment and position of the clipping plane,
	// Where the forward vector will be used as the plane normal
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FComponentReference ScreenComponentRef;

	// The scene capture component that this component will manage the clipping plane for
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> SceneCaptureActor;

	// The CineCamera component that the inner frustum is rendering from
	// This component will manipulate its near plane distance to match it to the screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ACineCameraActor> CineCameraActor;

	// To allow configuration for clipping foreground or background
	// depending on which composure layer this component is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bFlipClippingPlane = false;

	bool bIsSetUpCorrect = false;
};
