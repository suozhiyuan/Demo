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
	//��ȡGameStyle
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
	//��ʼ����������
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
			//������һ������
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

	//��ʼ����Ϸ��������
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

	//��ʼ��һ���˳���Ϸ��ť
	SAssignNew(QuitGameButton, SButton)
		.OnClicked(this, &SDemoGameMenuWidget::QuitGameEvent)
		.HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("DemoGame", "QuitGame", "QuitGame"))
			.Font(GameStyle->Font_30)
		];

	//���˵���ť���
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
	//���
	VertBox->ClearChildren();

	//�����ÿؼ����
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

	//���ø߶�
	RootBox->SetHeightOverride(520.f);
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::SaveGameEvent()
{
	//����浵
	SaveGameDele.ExecuteIfBound();
	//����SaveGame��ť������
	SaveGameButton->SetVisibility(EVisibility::HitTestInvisible);
	//�޸Ĵ浵����
	SaveGameText->SetText(NSLOCTEXT("DemoGame", "SaveCompleted", "SaveCompleted"));
	//����
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::QuitGameEvent()
{
	Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
	return FReply::Handled();
}

FReply SDemoGameMenuWidget::GoBackEvent()
{
	//���
	VertBox->ClearChildren();
	//���˵���ť���
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
	//���ø߶�
	RootBox->SetHeightOverride(400.f);
	return FReply::Handled();
}

void SDemoGameMenuWidget::ChangeCulture(ECultureTeam Cultrue)
{
	DemoDataHandle::Get()->ChangeLocalizationCulture(Cultrue);
}

void SDemoGameMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	// ��ȡDemoDataHandle������ֱ���޸�����
	DemoDataHandle::Get()->ResetGameVolume(MusicVolume, SoundVolume);
}

void SDemoGameMenuWidget::GameLose()
{
	//���
	VertBox->ClearChildren();

	VertBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(10.f)
		.FillHeight(1.f)
		[
			QuitGameButton->AsShared()
		];

	//���ø߶�
	RootBox->SetHeightOverride(200.f);
}

void SDemoGameMenuWidget::ResetMenu()
{
	//���
	VertBox->ClearChildren();

	//���˵���ť���
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
	//���ø߶�
	RootBox->SetHeightOverride(400.f);
	//���ô浵��ť
	SaveGameButton->SetVisibility(EVisibility::Visible);
	//�޸Ĵ浵����
	SaveGameText->SetText(NSLOCTEXT("DemoGame", "SaveGame", "SaveGame"));
}
