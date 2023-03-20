// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSlider.h"

//修改中英文委托
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)			// 委托名，参数
//修改音量委托
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)		// 委托名，参数，参数


class DEMO_API SDemoGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	//统一设置样式
	void StyleInitialize();

	//中文CheckBox事件
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//英文CheckBox事件
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
	//音量变化事件
	void MusicSliderChanged(float Value);
	void SoundSliderChanged(float Value);

private:
	//获取MenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//获取CheckBox指针
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;

	//两个进度条，SSlider是Slate滑块控件，是一个线性缩放和可拖动的内容
	TSharedPtr<SSlider> MuSlider;		//背景音乐
	TSharedPtr<SSlider> SoSlider;		//音效

	//进度条百分比，STextBlock 是一个简单的静态文本小部件
	TSharedPtr<STextBlock> MuTextBlock;			// 
	TSharedPtr<STextBlock> SoTextBlock;

	//委托变量
	FChangeCulture ChangeCulture;		// 语言
	FChangeVolume ChangeVolume;			// 音量
};
