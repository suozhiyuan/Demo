// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoShortcutWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoShortcutWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	ChildSlot
		[
			SNew(SBox)				// 快捷栏大底
			.WidthOverride(900.f)
			.HeightOverride(160.f)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()			// 快捷栏上方的物品信息
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SAssignNew(ShortcutInfoTextBlock, STextBlock)
					.Font(GameStyle->Font_Outline_40)
					.ColorAndOpacity(GameStyle->FontColor_White)
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.f, 60.f, 0.f, 0.f))
				[
					SAssignNew(GridPanel, SUniformGridPanel)	// 快捷栏网格	
				]
			]
		];

	//设置没有初始化容器
	IsInitializeContainer = false;
}

void SDemoShortcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer)			// 因为 SlateWidget 是没有BeginPlay函数的，所以要在 Tick 的第一帧去运行，以保证去运行委托
	{
		InitializeContainer();
		IsInitializeContainer = true;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SDemoShortcutWidget::InitializeContainer()
{
	TArray<TSharedPtr<ShortcutContainer>> ContainerList;		// 快捷栏中的容器 组成的数组

	for (int i = 0; i < 9; ++i) 
	{
		//创建容器
		TSharedPtr<SBorder> ContainerBorder;			// 快捷栏的一个格子
		TSharedPtr<SBorder> ObjectImage;				// 快捷栏图标
		TSharedPtr<STextBlock> ObjectNumText;			// 快捷栏图标上的文字

		SAssignNew(ContainerBorder, SBorder)
		.Padding(FMargin(10.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 5.f, 0.f))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		];

		//将容器添加到网格
		GridPanel->AddSlot(i, 0)		// 第几列 第几行
		[
			ContainerBorder->AsShared()
		];

		//实例化一个容器结构体
		TSharedPtr<ShortcutContainer> Container = MakeShareable(new ShortcutContainer(ContainerBorder, ObjectImage, ObjectNumText, &GameStyle->NormalContainerBrush, &GameStyle->ChoosedContainerBrush, &DemoDataHandle::Get()->ObjectBrushList));

		//如果是第一个容器,设置他为选中状态
		if (i == 0) Container->SetChoosed(true);

		ContainerList.Add(Container);

	}

	//将实例化的结构体注册进 PlayerState 的容器数组
	RegisterShortcutContainer.ExecuteIfBound(&ContainerList, ShortcutInfoTextBlock);

}
