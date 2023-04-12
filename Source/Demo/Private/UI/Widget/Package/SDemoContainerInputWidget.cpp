// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerInputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoContainerInputWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/

	/*SDemoContainerBaseWidget::Construct(
		SDemoContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex)
	);*/
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//void SDemoContainerInputWidget::ResetContainerPara(int ObjectID, int Num)
//{
//	//定义是否改变
//	bool IsChanged = false;
//	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;
//
//	//调用父类事件
//	SDemoContainerBaseWidget::ResetContainerPara(ObjectID, Num);
//
//	//如果有改变,就执行合成输入委托
//	if (IsChanged) CompoundInput.ExecuteIfBound();
//}
