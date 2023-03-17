// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DemoMenuGameMode.h"
#include "GamePlay/DemoMenuController.h"
#include "UI/HUD/DemoMenuHUD.h"

ADemoMenuGameMode::ADemoMenuGameMode()
{
	PlayerControllerClass = ADemoMenuController::StaticClass();
	HUDClass = ADemoMenuHUD::StaticClass();
}

