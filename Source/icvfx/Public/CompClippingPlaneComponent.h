// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CompClippingPlaneComponent.generated.h"

/*
 * A simple component to manage clipping planes for Composure layers
 * It will align a clipping plane for a scene capture component with a nDisplay screen
 * Assumes FLAT nDisplay geometry
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ICVFX_API UCompClippingPlaneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCompClippingPlaneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	void FindSceneCaptureComponent();

protected:
	// The scene capture component that this component will manage the clipping plane for
	UPROPERTY()
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent = nullptr;

	// The screen to align the clipping plane with.
	// Specify a scene component in the editor, usually the nDisplay Screen/Static Mesh used for displaying the backplate
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FComponentReference ScreenComponentRef;

	// To allow configuration for clipping foreground or background
	// depending on which composure layer this component is applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bClipForeground = false;
};
