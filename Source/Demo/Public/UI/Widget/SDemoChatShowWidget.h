// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

struct  ChatShowItem;
/**
 *
 */
class DEMO_API SDemoChatShowWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoChatShowWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//添加信息
	void AddMessage(FText NewName, FText NewContent);

private:

	void InitlizeItem();


private:

	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	TSharedPtr<SVerticalBox> ChatBox;

	//已经激活的序列
	TArray<TSharedPtr<ChatShowItem>> ActiveList;

	//未激活的序列
	TArray<TSharedPtr<ChatShowItem>> UnActiveList;
};
