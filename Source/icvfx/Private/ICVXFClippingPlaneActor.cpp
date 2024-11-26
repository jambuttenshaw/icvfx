// Fill out your copyright notice in the Description page of Project Settings.

#include "ICVXFClippingPlaneActor.h"
#include "ICVXFClippingPlaneComponent.h"


// Sets default values
AICVXFClippingPlaneActor::AICVXFClippingPlaneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	ClippingPlaneComponent = CreateDefaultSubobject<UICVXFClippingPlaneComponent>(TEXT("Clipping Plane Component"));
}
