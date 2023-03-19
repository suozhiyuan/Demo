// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuItemWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuItemWidget::Construct(const FArguments& InArgs)
{
	//获取MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");


	OnClicked = InArgs._OnClicked;		// InArgs 可以获取到当前类定义的所有东西
	ItemType = InArgs._ItemType.Get();

	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(500.f)
			.HeightOverride(100.f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuItemBrush)
						.ColorAndOpacity(this, &SDemoMenuItemWidget::GetTintColor)	// 如果颜色有变化则会调用
					]

				+ SOverlay::Slot()		// 放文字
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(InArgs._ItemText)
						.Font(MenuStyle->Font_60)
					]
			]
		];

	//初始化
	IsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


// 实现了简单的 SButton 方法
FReply SDemoMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true;
	return FReply::Handled();
}

FReply SDemoMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//如果按钮按下了并且OnClicked委托绑定有方法那就执行
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);			// 鼠标弹起时触发事件， ExecuteIfBound 判断是否绑定，绑定了就执行
	}
	return FReply::Handled();
}

void SDemoMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = false;
}

FSlateColor SDemoMenuItemWidget::GetTintColor() const
{
	if (IsMouseButtonDown) return FLinearColor(1.f, 0.1f, 0.1f, 0.5f);
	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
