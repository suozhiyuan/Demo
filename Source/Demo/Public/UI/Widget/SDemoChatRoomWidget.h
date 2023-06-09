// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

struct ChatMessItem;

DECLARE_DELEGATE_TwoParams(FPushMessage, FText, FText)
/**
 *
 */
class DEMO_API SDemoChatRoomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoChatRoomWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//提交事件
	void SubmitEvent(const FText& SubmitText, ETextCommit::Type CommitType);

	//按钮事件
	FReply SendEvent();

	//添加信息
	void AddMessage(FText NewName, FText NewContent);

	//滑动到最底下
	void ScrollToEnd();

public:

	FPushMessage PushMessage;

private:

	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	//滚动框
	TSharedPtr<class SScrollBox> ScrollBox;

	//保存输入框
	TSharedPtr<class SEditableTextBox> EditTextBox;

	//保存数组
	TArray<TSharedPtr<ChatMessItem>> MessageList;
};
