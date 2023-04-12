// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerShortcutWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoContainerShortcutWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/

	// 通过调用父类的 Construct 函数，获取子类的 _WorkIndex 传递给父类的 _WorkIndex
	SDemoContainerBaseWidget::Construct(
		SDemoContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex) 
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//
//void SDemoContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
//{
//	//定义是否改变
//	bool IsChanged = false;
//	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;
//
//	//调用父类事件
//	SDemoContainerBaseWidget::ResetContainerPara(ObjectID, Num);
//
//
//	//如果有改变, 执行快捷栏修改更新委托,传出快捷栏序号以及新的物品ID
//	if (IsChanged) PackShortChange.ExecuteIfBound(WorkIndex.Get(), ObjectID, Num);
//}
//
