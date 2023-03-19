// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"


DECLARE_DELEGATE_OneParam(FItemClicked, const EMenuItem::Type)		// 传入1个参数并且没有返回的委托，其中第一个参数为委托名，第二个参数为传入的参数

/**
 * 
 */
class DEMO_API SDemoMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText, ItemText)				// 使用此宏后，widget的声明中将可以添加相关属性，属性可以是值或函数
	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)
	SLATE_EVENT(FItemClicked, OnClicked)			// 使用此宏将处理添加到widget的事件。这个widget要有一个委托，参数1 委托名，参数2 调用事件
	

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	//重写组件的 OnMouseButtonDown 方法
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//重写按钮起来的方法
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//鼠标离开
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;


private:
	//获取颜色
	FSlateColor GetTintColor() const;

private:

	//获取MenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//按下事件委托
	FItemClicked OnClicked;

	//保存按钮类型
	EMenuItem::Type ItemType;

	//按钮是否已经按下
	bool IsMouseButtonDown;
};
