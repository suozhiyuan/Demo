// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DemoMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoMenuHUD : public AHUD
{
	GENERATED_BODY()

	ADemoMenuHUD();

	TSharedPtr<class SDemoMenuHUDWidget> MenuHUDWidget;

};
