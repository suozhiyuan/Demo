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
//	//�����Ƿ�ı�
//	bool IsChanged = false;
//	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;
//
//	//���ø����¼�
//	SDemoContainerBaseWidget::ResetContainerPara(ObjectID, Num);
//
//	//����иı�,��ִ�кϳ�����ί��
//	if (IsChanged) CompoundInput.ExecuteIfBound();
//}
