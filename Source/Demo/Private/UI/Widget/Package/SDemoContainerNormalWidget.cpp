// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerNormalWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoContainerNormalWidget::Construct(const FArguments& InArgs)
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
