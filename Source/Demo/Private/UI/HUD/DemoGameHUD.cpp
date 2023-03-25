// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DemoGameHUD.h"

#include "GamePlay/DemoGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerState.h"
#include "UI/Widget/SDemoGameHUDWidget.h"
#include "SlateBasics.h"

ADemoGameHUD::ADemoGameHUD()
{
	if (GEngine && GEngine->GameViewport)		// GameViewport ��ʾ��ǰ��Ϸʵ������ͼ�˿�
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
	////��ȷ��Ҫ���õ�������Ѿ�ʵ��
	//GM->InitGamePlayModule();
	////��ע����������
	//GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ADemoPlayerState::RegisterShortcutContainer);
	////��ע��������Ϣ�ı��¼�
	//GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->SPState, &ADemoPlayerState::RegisterRayInfoEvent);
	////���޸�׼��ί��
	//GM->SPController->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(), &SDemoPointerWidget::UpdatePointer);
	////�󶨸������״̬��ί��
	//GM->SPState->UpdateStateWidget.BindRaw(GameHUDWidget->PlayerStateWidget.Get(), &SDemoPlayerStateWidget::UpdateStateWidget);
	////����ʾUIί��
	//GM->SPController->ShowGameUI.BindRaw(GameHUDWidget.Get(), &SDemoGameHUDWidget::ShowGameUI);
	////��ʼ���������������������
	//GM->InitPackageManager.BindRaw(GameHUDWidget->PackageWidget.Get(), &SDemoPackageWidget::InitPackageManager);
	////��ע��С��ͼ��ͼί��
	//GM->RegisterMiniMap.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SDemoMiniMapWidget::RegisterMiniMap);
	////�󶨸���С��ͼ����ί��
	//GM->UpdateMapData.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SDemoMiniMapWidget::UpdateMapData);
	////������Ϸ�¼���
	//GameHUDWidget->GameMenuWidget->SaveGameDele.BindUObject(GM, &ADemoGameMode::SaveGame);
}



