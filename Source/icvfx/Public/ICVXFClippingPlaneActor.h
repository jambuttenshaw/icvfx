// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICVXFClippingPlaneActor.generated.h"

class UICVXFClippingPlaneComponent;

/*
 * An actor that contains an ICVFXClippingPlaneComponent.
 */
UCLASS(BlueprintType, Blueprintable)
class ICVFX_API AICVXFClippingPlaneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AICVXFClippingPlaneActor();

protected:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
	UICVXFClippingPlaneComponent* ClippingPlaneComponent = nullptr;
};
