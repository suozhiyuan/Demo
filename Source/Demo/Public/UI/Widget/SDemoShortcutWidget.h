// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


////注册快捷栏到PlayerState类的委托
//DECLARE_DELEGATE_TwoParams(FRegisterShortCutContainer, TArray<TSharedPtr<ShortcutContainer>>*, TSharedPtr<STextBlock>)

/**
*
*/
class DEMO_API SDemoShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

//public:
//
//	FRegisterShortCutContainer RegisterShortcutContainer;

private:

	//初始化所有容器
	void InitializeContainer();

private:

	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	//物品信息的指针
	TSharedPtr<class STextBlock> ShortcutInfoTextBlock;

	//网格指针
	TSharedPtr<class SUniformGridPanel> GridPanel;

	//是否初始化容器
	bool IsInitializeContainer;

};
