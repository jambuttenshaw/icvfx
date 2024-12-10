// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CompositingElements/CompositingElementTransforms.h"
#include "CameraAwareMaterialPass.generated.h"

/**
 * A specialized form of Compositing Element Material Pass that allows access to the camera properties that originally captured the pass.
 * This is useful if you need to reconstruct world-space positions from a depth map, for example.
 */
UCLASS(BlueprintType, Blueprintable, editinlinenew)
class ICVFX_API UCameraAwareMaterialPass : public UCompositingElementMaterialPass
{
	GENERATED_BODY()

public:
	/**
	 * The camera actor that this pass will collect the properties from when performing this transform pass.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Compositing Pass", meta = (ShowOnlyInnerProperties, EditCondition = "bEnabled"))
	TObjectPtr<AActor> SceneCaptureActor;
	
protected:

	UFUNCTION(BlueprintCallable, Category = "Compositing Pass")
	void ApplyCameraParams(UMaterialInstanceDynamic* MID);

};
