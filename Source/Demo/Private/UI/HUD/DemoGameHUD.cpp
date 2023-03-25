// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DemoGameHUD.h"

#include "GamePlay/DemoGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerState.h"
#include "UI/Widget/SDemoGameHUDWidget.h"
#include "SlateBasics.h"

ADemoGameHUD::ADemoGameHUD()
{
	if (GEngine && GEngine->GameViewport)		// GameViewport 表示当前游戏实例的视图端口
	{
		SAssignNew(GameHUDWidget, SDemoGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}

void ADemoGameHUD::BeginPlay()
{
	Super::BeginPlay();

	//GM = Cast<ADemoGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//if (!GM) return;
	////先确保要调用的组件都已经实现
	//GM->InitGamePlayModule();
	////绑定注册快捷栏容器
	//GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ADemoPlayerState::RegisterShortcutContainer);
	////绑定注册射线信息文本事件
	//GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->SPState, &ADemoPlayerState::RegisterRayInfoEvent);
	////绑定修改准星委托
	//GM->SPController->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(), &SDemoPointerWidget::UpdatePointer);
	////绑定更新玩家状态的委托
	//GM->SPState->UpdateStateWidget.BindRaw(GameHUDWidget->PlayerStateWidget.Get(), &SDemoPlayerStateWidget::UpdateStateWidget);
	////绑定显示UI委托
	//GM->SPController->ShowGameUI.BindRaw(GameHUDWidget.Get(), &SDemoGameHUDWidget::ShowGameUI);
	////初始化背包管理器到背包组件
	//GM->InitPackageManager.BindRaw(GameHUDWidget->PackageWidget.Get(), &SDemoPackageWidget::InitPackageManager);
	////绑定注册小地图贴图委托
	//GM->RegisterMiniMap.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SDemoMiniMapWidget::RegisterMiniMap);
	////绑定更新小地图数据委托
	//GM->UpdateMapData.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SDemoMiniMapWidget::UpdateMapData);
	////保存游戏事件绑定
	//GameHUDWidget->GameMenuWidget->SaveGameDele.BindUObject(GM, &ADemoGameMode::SaveGame);
}



