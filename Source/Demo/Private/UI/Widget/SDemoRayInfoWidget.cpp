// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoRayInfoWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoGameWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoRayInfoWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(400.f)
		.HeightOverride(100.f)
		[
			SNew(SBorder)
			.BorderImage(&GameStyle->RayInfoBrush)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RayInfoTextBlock, STextBlock)
				.Font(GameStyle->Font_Outline_50)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoRayInfoWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//第一帧的时候进行初始化
	if (!IsInitRayInfoEvent)
	{
		RegisterRayInfoEvent.ExecuteIfBound(RayInfoTextBlock);
		IsInitRayInfoEvent = true;
	}
}
