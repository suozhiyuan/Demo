// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoMenuHUDWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
		[
			SNew(SButton)
		];
		////获取编辑器的MenuStyle
		//MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
		////绑定缩放规则方法
		//UIScaler.Bind(this, &SSlAiMenuHUDWidget::GetUIScaler);

		//ChildSlot
		//	[
		//		SNew(SDPIScaler)
		//		.DPIScale(UIScaler)
		//	[
		//		SNew(SOverlay)

		//		+ SOverlay::Slot()
		//	.HAlign(HAlign_Fill)
		//	.VAlign(VAlign_Fill)
		//	[
		//		SNew(SImage)
		//		.Image(&MenuStyle->MenuHUDBackgroundBrush)
		//	]

		//+ SOverlay::Slot()
		//	.HAlign(HAlign_Center)
		//	.VAlign(VAlign_Center)
		//	[
		//		SAssignNew(MenuWidget, SSlAiMenuWidget)
		//	]

		//	]
		//	];

	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
