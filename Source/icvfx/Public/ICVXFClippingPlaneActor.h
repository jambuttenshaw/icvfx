// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICVXFClippingPlaneActor.generated.h"

class UICVXFClippingPlaneComponent;

UCLASS(BlueprintType, Blueprintable)
class ICVFX_API AICVXFClippingPlaneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AICVXFClippingPlaneActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite)
	UICVXFClippingPlaneComponent* ClippingPlaneComponent = nullptr;
};
