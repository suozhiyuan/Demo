// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "Widgets/Layout/SDPIScaler.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuHUDWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");			//获取编辑器的MenuStyle

	//绑定缩放规则方法
	UIScaler.Bind(this, &SDemoMenuHUDWidget::GetUIScaler);

	ChildSlot
		[
			SNew(SDPIScaler)
			.DPIScale(UIScaler)		// 下一层级所有的组件都会更具 UIScaler 的值进行缩放
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuHUDBackgroundBrush)	// 实例化一个Image组件，添加Image并且添加一个笔刷
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						//SAssignNew(MenuWidget, SSlAiMenuWidget)
						SNew(SImage)
						.Image(&MenuStyle->MenuBackgroundBrush)
					]
			]
		];
}

//绑定UIScaler的函数
float SDemoMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

//获取屏幕尺寸
FVector2D SDemoMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(Result);
	return Result;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
