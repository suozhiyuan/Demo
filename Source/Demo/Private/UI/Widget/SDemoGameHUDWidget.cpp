// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "UI/Widget/SDemoPointerWidget.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "UI/Widget/SDemoShortcutWidget.h"
#include "UI/Widget/SDemoRayInfoWidget.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoGameHUDWidget::Construct(const FArguments& InArgs)
{

	UIScaler.Bind(this, &SDemoGameHUDWidget::GetUIScaler);

	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()			//�����
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget, SDemoShortcutWidget)
			]


			//������Ϣ
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget, SDemoRayInfoWidget)
			]


			//׼��
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(PointerWidget, SDemoPointerWidget)
			]

			////���״̬
			//+ SOverlay::Slot()
			//	.HAlign(HAlign_Left)
			//	.VAlign(VAlign_Top)
			//	[
			//		SAssignNew(PlayerStateWidget, SDemoPlayerStateWidget)
			//	]

			////С��ͼ
			//+ SOverlay::Slot()
			//	.HAlign(HAlign_Right)
			//	.VAlign(VAlign_Top)
			//	[
			//		SAssignNew(MiniMapWidget, SDemoMiniMapWidget)
			//	]


			////������ʾ��
			//+SOverlay::Slot()
			//	.HAlign(HAlign_Left)
			//	.VAlign(VAlign_Bottom)
			//	.Padding(FMargin(20.f, 0.f, 0.f, 15.f))
			//	[
			//		SAssignNew(ChatShowWidget, SDemoChatShowWidget)
			//	]



	////����ɫ����,�����¼��������ϷUI�м�
	//+SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Fill)
	//	[
	//		SAssignNew(BlackShade, SBorder)
	//		//����Ϊ��ɫ͸��
	//	.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f, 0.2f, 0.2f, 0.5f)))
	//	//��ʼʱ���ò���ʾ
	//	.Visibility(EVisibility::Hidden)
	//	[
	//		SNew(SImage)
	//	]
	//	]

	////GameMenu
	//+ SOverlay::Slot()
	//	.HAlign(HAlign_Center)
	//	.VAlign(VAlign_Center)
	//	[
	//		SAssignNew(GameMenuWidget, SDemoGameMenuWidget)
	//		.Visibility(EVisibility::Hidden)
	//	]

	////chatRoom
	//+ SOverlay::Slot()
	//	.HAlign(HAlign_Left)
	//	.VAlign(VAlign_Bottom)
	//	[
	//		SAssignNew(ChatRoomWidget, SDemoChatRoomWidget)
	//		.Visibility(EVisibility::Hidden)
	//	]


	////Package
	//+SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Fill)
	//	[
	//		SAssignNew(PackageWidget, SDemoPackageWidget)
	//		//����DPI
	//	.UIScaler(UIScaler)
	//	.Visibility(EVisibility::Hidden)
	//	]
		]
	];

	//InitUIMap();
}

//void SDemoGameHUDWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//
//	//ÿ�������һ����Ϣ
//	if (MessageTimeCount < 5.f) {
//		MessageTimeCount += InDeltaTime;
//	}
//	else
//	{
//		ChatShowWidget->AddMessage(NSLOCTEXT("DemoGame", "Enemy", "Enemy"), NSLOCTEXT("DemoGame", "EnemyDialogue", ": Fight with me !"));
//		ChatRoomWidget->AddMessage(NSLOCTEXT("DemoGame", "Enemy", "Enemy"), NSLOCTEXT("DemoGame", "EnemyDialogue", ": Fight with me !"));
//		MessageTimeCount = 0.f;
//	}
//
//}
//

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SDemoGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

//void SDemoGameHUDWidget::ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI)
//{
//	//���ǰһģʽ��Game,˵��Ҫ��ʾ�ڰ�
//	if (PreUI == EGameUIType::Game)
//	{
//		BlackShade->SetVisibility(EVisibility::Visible);
//	}
//	else
//	{
//		//���ص�ǰ������ʾ��UI
//		UIMap.Find(PreUI)->Get()->SetVisibility(EVisibility::Hidden);
//	}
//	//�����һģʽ��Game,���غڰ�
//	if (NextUI == EGameUIType::Game)
//	{
//		BlackShade->SetVisibility(EVisibility::Hidden);
//	}
//	else
//	{
//		//��ʾ����״̬��Ӧ��UI
//		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);
//		//��ʾ����״̬��Ӧ��UI
//		if (NextUI == EGameUIType::ChatRoom) ChatRoomWidget->ScrollToEnd();
//		//�����ʧ��,ֻ��ʾһ����ť
//		if (NextUI == EGameUIType::Lose) GameMenuWidget->GameLose();
//		//����ǲ˵�,���ò˵���ʼ��
//		if (NextUI == EGameUIType::Pause) GameMenuWidget->ResetMenu();
//	}
//
//}

FVector2D SDemoGameHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920.f, 1080.f);
	if (GEngine && GEngine->GameViewport) 
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}

//void SDemoGameHUDWidget::InitUIMap()
//{
//	UIMap.Add(EGameUIType::Pause, GameMenuWidget);
//	UIMap.Add(EGameUIType::Package, PackageWidget);
//	UIMap.Add(EGameUIType::ChatRoom, ChatRoomWidget);
//	UIMap.Add(EGameUIType::Lose, GameMenuWidget);
//
//	//��ί��
//	ChatRoomWidget->PushMessage.BindRaw(ChatShowWidget.Get(), &SDemoChatShowWidget::AddMessage);
//	//��Ϣ��ʱ����ʼ����Ϊ0
//	MessageTimeCount = 0.f;
//}
