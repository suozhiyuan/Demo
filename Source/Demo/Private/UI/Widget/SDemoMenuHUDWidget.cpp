// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");
	////绑定缩放规则方法
	//UIScaler.Bind(this, &SSlAiMenuHUDWidget::GetUIScaler);

	ChildSlot
		[
			//SNew(SButton)
			SNew(SImage)
			.Image(&MenuStyle->MenuHUDBackgroundBrush)	// 实例化一个Image组件，添加Image并且添加一个笔刷
		];

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
