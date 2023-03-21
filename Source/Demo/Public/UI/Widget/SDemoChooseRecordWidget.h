// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


/**
 *
 */
class DEMO_API SDemoChooseRecordWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoChooseRecordWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs);

	//更新存档名
	void UpdateRecordName();

private:

	//获取MenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//下拉菜单
	TSharedPtr<STextComboBox> RecordComboBox;

	//字符指针数组
	TArray<TSharedPtr<FString>> OptionsSource;

};
