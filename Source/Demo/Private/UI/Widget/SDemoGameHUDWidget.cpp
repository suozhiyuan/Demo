// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "UI/Widget/SDemoChatRoomWidget.h"
#include "UI/Widget/SDemoGameMenuWidget.h"
#include "UI/Widget/SDemoPlayerStateWidget.h"
#include "UI/Widget/SDemoPointerWidget.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "UI/Widget/SDemoShortcutWidget.h"
#include "UI/Widget/SDemoRayInfoWidget.h"
#include "UI/Widget/Package/SDemoPackageWidget.h"
#include "Widgets/Images/SImage.h"


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

			+ SOverlay::Slot()			//快捷栏
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget, SDemoShortcutWidget)
			]


			//射线信息
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget, SDemoRayInfoWidget)
			]


			//准星
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(PointerWidget, SDemoPointerWidget)
			]

			//玩家状态
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SAssignNew(PlayerStateWidget, SDemoPlayerStateWidget)
			]

			////小地图
			//+ SOverlay::Slot()
			//	.HAlign(HAlign_Right)
			//	.VAlign(VAlign_Top)
			//	[
			//		SAssignNew(MiniMapWidget, SDemoMiniMapWidget)
			//	]


			////聊天显示栏
			//+SOverlay::Slot()
			//	.HAlign(HAlign_Left)
			//	.VAlign(VAlign_Bottom)
			//	.Padding(FMargin(20.f, 0.f, 0.f, 15.f))
			//	[
			//		SAssignNew(ChatShowWidget, SDemoChatShowWidget)
			//	]



			//暗黑色遮罩,放在事件界面和游戏UI中间
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(BlackShade, SBorder)
				//设置为黑色透明
				.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f, 0.2f, 0.2f, 0.5f)))
				//开始时设置不显示
				.Visibility(EVisibility::Hidden)		// EVisibility::Hidden  不显示
				[
					SNew(SImage)								// 这个 SImage 默认时白色的，会应用上边设置的透明度与颜色
				]
			]

			// GameMenu
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(GameMenuWidget, SDemoGameMenuWidget)
				.Visibility(EVisibility::Hidden)
			]

			// chatRoom
			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ChatRoomWidget, SDemoChatRoomWidget)
				.Visibility(EVisibility::Hidden)
			]

			// Package
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(PackageWidget, SDemoPackageWidget)
				//设置DPI
				//.UIScaler(UIScaler)
				.Visibility(EVisibility::Hidden)
			]
		]
	];

	InitUIMap();
}

//void SDemoGameHUDWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//
//	//每五秒插入一条信息
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

void SDemoGameHUDWidget::ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI)
{
	//如果前一模式是Game,说明要显示黑色遮罩
	if (PreUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Visible);		// EVisibility::Visible 可见
	}
	else
	{
		//如果前一模式不是Game，则隐藏当前正在显示的UI
		UIMap.Find(PreUI)->Get()->SetVisibility(EVisibility::Hidden);		// EVisibility::Hidden 不可见
	}

	//如果下一模式是Game, 隐藏黑色遮罩
	if (NextUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Hidden);
	}
	else
	{
		//显示现在状态对应的UI
		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);

		////显示现在状态对应的UI
		//if (NextUI == EGameUIType::ChatRoom) ChatRoomWidget->ScrollToEnd();

		////如果是失败,只显示一个按钮
		//if (NextUI == EGameUIType::Lose) GameMenuWidget->GameLose();

		////如果是菜单,设置菜单初始化
		//if (NextUI == EGameUIType::Pause) GameMenuWidget->ResetMenu();
	}
}

FVector2D SDemoGameHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920.f, 1080.f);
	if (GEngine && GEngine->GameViewport) 
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}

void SDemoGameHUDWidget::InitUIMap()
{
	UIMap.Add(EGameUIType::Pause, GameMenuWidget);
	UIMap.Add(EGameUIType::Package, PackageWidget);
	UIMap.Add(EGameUIType::ChatRoom, ChatRoomWidget);
	UIMap.Add(EGameUIType::Lose, GameMenuWidget);

	////绑定委托
	//ChatRoomWidget->PushMessage.BindRaw(ChatShowWidget.Get(), &SDemoChatShowWidget::AddMessage);

	////消息计时器初始设置为0
	//MessageTimeCount = 0.f;
}
