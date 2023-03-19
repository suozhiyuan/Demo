// Fill out your copyright notice in the De7scription page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DEMO_API SDemoMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//绑定UIScaler的函数
	float GetUIScaler() const;

	//获取屏幕尺寸
	FVector2D GetViewportSize() const;

	///*
	// * Reply是一个Slate事件返回给系统的东西，通知它一个事件是如何处理的。
	// * 例如，一个小部件可能会处理一个OnlouseDown事件，要求系统给一个特定的小部件鼠标捕获。
	// * 为此，返回FReply::CaptureMouse (NewMouseCapture)
	// */
	//FReply OnClick();		


private:
	//获取Menu样式
	const struct FDemoMenuStyle* MenuStyle;

	//DPI缩放系数
	TAttribute<float> UIScaler;

	//菜单指针
	TSharedPtr<class SDemoMenuWidget> MenuWidget;

	//// 获取Image的Slot 对其进行修改, 这个变量要在要修改的 + SOverlay::Slot() 下进行 .Expose(ImageSlot)
	//SOverlay::FOverlaySlot* ImageSlot;
};
