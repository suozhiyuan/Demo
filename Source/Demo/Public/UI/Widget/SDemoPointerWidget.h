// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


/**
 *
 */
class DEMO_API SDemoPointerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoPointerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//给PlayerController绑定的事件,修改准星是否锁定以及加载进度
	void UpdatePointer(bool IsAim, float Range);

private:

	//给SBox大小变化绑定的函数
	FOptionalSize GetBoxWidget() const;
	FOptionalSize GetBoxHeight() const;

private:
	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	TSharedPtr<class SBox> RootBox;

	//实时改变的大小,改变这个变量就可以改变准星大小
	float CurrentSize;

	//获取材质实例
	class UMaterialInstanceDynamic* PointerMaterial;

	//是否改变大小状态
	bool IsAimed;

};
