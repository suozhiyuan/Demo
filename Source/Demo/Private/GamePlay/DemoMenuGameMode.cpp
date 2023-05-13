// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DemoMenuGameMode.h"
#include "GamePlay/DemoMenuController.h"
#include "UI/HUD/DemoMenuHUD.h"
#include "GamePlay/DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

ADemoMenuGameMode::ADemoMenuGameMode()
{
	PlayerControllerClass = ADemoMenuController::StaticClass();
	HUDClass = ADemoMenuHUD::StaticClass();
}

void ADemoMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("Demo");
}

