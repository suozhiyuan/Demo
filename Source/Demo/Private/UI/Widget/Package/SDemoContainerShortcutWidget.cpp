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

	// ͨ�����ø���� Construct ��������ȡ����� _WorkIndex ���ݸ������ _WorkIndex
	SDemoContainerBaseWidget::Construct(
		SDemoContainerBaseWidget::FArguments()
		.WorkIndex(InArgs._WorkIndex) 
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//
//void SDemoContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
//{
//	//�����Ƿ�ı�
//	bool IsChanged = false;
//	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;
//
//	//���ø����¼�
//	SDemoContainerBaseWidget::ResetContainerPara(ObjectID, Num);
//
//
//	//����иı�, ִ�п�����޸ĸ���ί��,�������������Լ��µ���ƷID
//	if (IsChanged) PackShortChange.ExecuteIfBound(WorkIndex.Get(), ObjectID, Num);
//}
//
