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

	//�����Ϣ
	void AddMessage(FText NewName, FText NewContent);

private:

	void InitlizeItem();


private:

	//��ȡGameStyle
	const struct FDemoGameStyle* GameStyle;

	TSharedPtr<SVerticalBox> ChatBox;

	//�Ѿ����������
	TArray<TSharedPtr<ChatShowItem>> ActiveList;

	//δ���������
	TArray<TSharedPtr<ChatShowItem>> UnActiveList;
};
