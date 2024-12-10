// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraAwareMaterialPass.h"

#include "Kismet/GameplayStatics.h"


void UCameraAwareMaterialPass::ApplyCameraParams(UMaterialInstanceDynamic* MID)
{
	// Should be verified by caller
	check(MID != nullptr);

	if (!SceneCaptureActor)
		return;

	FMatrix ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;
	UGameplayStatics::CalculateViewProjectionMatricesFromViewTarget(SceneCaptureActor, ViewMatrix, ProjectionMatrix, ViewProjectionMatrix);

	//UE_LOG(LogTemp, Display, TEXT("Matrices:"));
	//ViewMatrix.DebugPrint();
	//ProjectionMatrix.DebugPrint();
	//ViewProjectionMatrix.DebugPrint();

	FMatrix InvProjMatrix = ProjectionMatrix.Inverse();

	// Takes the parameters from the camera and sends them into the material
	FLinearColor Row0(InvProjMatrix.M[0][0], InvProjMatrix.M[0][1], InvProjMatrix.M[0][2], InvProjMatrix.M[0][3]);
	FLinearColor Row1(InvProjMatrix.M[1][0], InvProjMatrix.M[1][1], InvProjMatrix.M[1][2], InvProjMatrix.M[1][3]);
	FLinearColor Row2(InvProjMatrix.M[2][0], InvProjMatrix.M[2][1], InvProjMatrix.M[2][2], InvProjMatrix.M[2][3]);
	FLinearColor Row3(InvProjMatrix.M[3][0], InvProjMatrix.M[3][1], InvProjMatrix.M[3][2], InvProjMatrix.M[3][3]);
	MID->SetVectorParameterValue(TEXT("InvViewProj_0"), Row0);
	MID->SetVectorParameterValue(TEXT("InvViewProj_1"), Row1);
	MID->SetVectorParameterValue(TEXT("InvViewProj_2"), Row2);
	MID->SetVectorParameterValue(TEXT("InvViewProj_3"), Row3);
}
