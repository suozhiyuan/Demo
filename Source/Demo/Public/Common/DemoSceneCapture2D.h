// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "DemoSceneCapture2D.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoSceneCapture2D : public ASceneCapture2D
{
	GENERATED_BODY()

public:

	ADemoSceneCapture2D();

	//获取MiniMapText
	UTextureRenderTarget2D* GetMiniMapTex();

	//更新变换
	void UpdateTransform(FVector NormLocation, FRotator NormRotator);

	//更新视野范围
	void UpdateMiniMapWidth(int Delta);

	//获取小地图尺寸
	float GetMapSize();

private:
	// 
	UTextureRenderTarget2D* MiniMapTex;
};
