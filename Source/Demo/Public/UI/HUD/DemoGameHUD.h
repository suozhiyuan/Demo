// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DemoGameHUD.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API ADemoGameHUD : public AHUD
{
	GENERATED_BODY()

public:

	ADemoGameHUD();
//
//public:

	////����GameModeָ��
	//class ADemoGameMode* GM;


protected:

	virtual void BeginPlay() override;


private:

	TSharedPtr<class SDemoGameHUDWidget> GameHUDWidget;

};
