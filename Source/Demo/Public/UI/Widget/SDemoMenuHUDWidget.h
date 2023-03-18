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
	////绑定UIScaler的函数
	//float GetUIScaler() const;

	////获取屏幕尺寸
	//FVector2D GetViewportSize() const;



private:
	//获取Menu样式
	const struct FDemoMenuStyle* MenuStyle;

	////DPI缩放系数
	//TAttribute<float> UIScaler;
	////菜单指针
	//TSharedPtr<class SDemoMenuWidget> MenuWidget;

};
