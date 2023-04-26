// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoGameMenuWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerController.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Widget/SDemoGameOptionWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoGameMenuWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	ChildSlot
		[
			SAssignNew(RootBox, SBox)
			.WidthOverride(600.f)
			.HeightOverride(400.f)
			.Padding(FMargin(50.f))
			[
				SAssignNew(VertBox, SVerticalBox)
			]
		];

	InitializeWidget();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoGameMenuWidget::InitializeWidget()
{
	//初始化正常界面
	MenuItemList.Add
	(
		SNew(SButton)
		.OnClicked(this, &SDemoGameMenuWidget::OptionEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("DemoGame", "GameOption", "GameOption"))
			.Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add
	(
		SAssignNew(SaveGameButton, SButton)
		.OnClicked(this, &SDemoGameMenuWidget::SaveGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			//这里做一个引用
			SAssignNew(SaveGameText, STextBlock)
			.Text(NSLOCTEXT("DemoGame", "SaveGame", "SaveGame"))
			.Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add
	(
		SNew(SButton)
		.OnClicked(this, &SDemoGameMenuWidget::QuitGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("DemoGame", "QuitGame", "QuitGame"))
			.Font(GameStyle->Font_30)
		]
	);

	//初始化游戏设置数组
	OptionItemList.Add
	(
		SNew(SDemoGameOptionWidget)
		.ChangeCulture(this, &SDemoGameMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SDemoGameMenuWidget::ChangeVolume)
	);
	OptionItemList.Add
	(
		SNew(SButton)
		.OnClicked(this, &SDemoGameMenuWidget::GoBackEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("DemoGame", "GoBack", "GoBack"))
			.Font(GameStyle->Font_30)
		]
	);

	//初始化一个退出游戏按钮
	SAssignNew(QuitGameButton, SButton)
		.OnClicked(this, &SDemoGameMenuWidget::QuitGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("DemoGame", "QuitGame", "QuitGame"))
			.Font(GameStyle->Font_30)
		];

	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			(*It)->AsShared()
		];
	}
}

FReply SDemoGameMenuWidget::OptionEvent()
{
	//清空
	VertBox->ClearChildren();

	//将设置控件填充
	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(3.2f)
		[
			OptionItemList[0]->AsShared()
		];
	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			OptionItemList[1]->AsShared()
		];

	//设置高度
	RootBox->SetHeightOverride(520.f);
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::SaveGameEvent()
{
	//保存存档
	SaveGameDele.ExecuteIfBound();
	//设置SaveGame按钮不可用
	SaveGameButton->SetVisibility(EVisibility::HitTestInvisible);
	//修改存档文字
	SaveGameText->SetText(NSLOCTEXT("DemoGame", "SaveCompleted", "SaveCompleted"));
	//返回
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::QuitGameEvent()
{
	Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::GoBackEvent()
{
	//清空
	VertBox->ClearChildren();
	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(10.f)
			.FillHeight(1.f)
			[
				(*It)->AsShared()
			];
	}
	//设置高度
	RootBox->SetHeightOverride(400.f);
	return FReply::Handled();
}

void SDemoGameMenuWidget::ChangeCulture(ECultureTeam Cultrue)
{
	DemoDataHandle::Get()->ChangeLocalizationCulture(Cultrue);
}

void SDemoGameMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	// 获取DemoDataHandle单例，直接修改音量
	DemoDataHandle::Get()->ResetGameVolume(MusicVolume, SoundVolume);
}

void SDemoGameMenuWidget::GameLose()
{
	//清空
	VertBox->ClearChildren();

	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			QuitGameButton->AsShared()
		];

	//设置高度
	RootBox->SetHeightOverride(200.f);
}

void SDemoGameMenuWidget::ResetMenu()
{
	//清空
	VertBox->ClearChildren();

	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(10.f)
			.FillHeight(1.f)
			[
				(*It)->AsShared()
			];
	}
	//设置高度
	RootBox->SetHeightOverride(400.f);
	//重置存档按钮
	SaveGameButton->SetVisibility(EVisibility::Visible);
	//修改存档文字
	SaveGameText->SetText(NSLOCTEXT("DemoGame", "SaveGame", "SaveGame"));
}
