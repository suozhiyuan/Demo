// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerOutputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoContainerOutputWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/

	//SDemoContainerBaseWidget::Construct(
	//	SDemoContainerBaseWidget::FArguments()
	//	.WorkIndex(InArgs._WorkIndex)
	//);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//
//void SDemoContainerOutputWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
//{
//	//���������ƷΪ��,����ɶ�ͷ���ɶ,ֱ��return
//	if (ObjectIndex == 0) {
//		OutputID = InputID;
//		OutputNum = InputNum;
//		return;
//	}
//
//	//���¶���������Ʒ��Ϊ�յ�״̬
//
//	//���������Ʒ�뱾����Ʒ��ͬ���ҿ��Ե���
//	if (InputID == ObjectIndex && MultiplyAble(InputID))
//	{
//		OutputID = ObjectIndex;
//		OutputNum = (InputNum + ObjectNum <= 64) ? (InputNum + ObjectNum) : 64;
//		ObjectNum = (InputNum + ObjectNum <= 64) ? 0 : (InputNum + ObjectNum - 64);
//		//ִ�кϳ����ί��
//		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
//		//ֱ��return
//		return;
//	}
//
//	//�����Ʒ����ͬ������Ʒ��ͬ���ǲ��ܵ���,�����Ʒ,����������Ʒ
//	OutputID = ObjectIndex;
//	OutputNum = ObjectNum;
//	//ִ�кϳ����ί��
//	CompoundOutput.ExecuteIfBound(ObjectIndex, ObjectNum);
//	//ִ�ж�����Ʒί��
//	ThrowObject.ExecuteIfBound(InputID, InputNum);
//
//}
//
//void SDemoContainerOutputWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
//{
//	//���������ƷΪ0
//	if (ObjectIndex == 0) {
//		OutputID = InputID;
//		OutputNum = InputNum;
//		return;
//	}
//
//	//���¶��Ǳ�����Ʒ��Ϊ0�����
//
//	//�������Ϊ��,ֱ�Ӹ������ص�һ��
//	if (InputID == 0) {
//		OutputID = ObjectIndex;
//		//������˫��
//		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
//		//ִ�кϳ����ί��
//		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
//		//��������
//		//ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
//		//ֱ�ӷ���
//		return;
//	}
//
//	//���¶������벻Ϊ�յ����
//
//	//�����Ʒ��ͬ���ҿ��Ժϲ�,����ȥһ��
//	if (InputID == ObjectIndex && MultiplyAble(InputID)) {
//		OutputID = ObjectIndex;
//		//Ԥ�����������
//		int PreOutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
//		//ʵ�����������
//		OutputNum = (PreOutputNum + InputNum <= 64) ? (PreOutputNum + InputNum) : 64;
//		//���±�������
//		ObjectNum = ObjectNum - (OutputNum - InputNum);
//		//ִ�кϳ����ί��
//		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
//		//��������
//		//ResetContainerPara(ObjectNum == 0 ? 0 : ObjectIndex, ObjectNum);
//		//ֱ�ӷ���
//		return;
//	}
//
//
//	//�����Ʒ����ͬ������ͬ���ǲ��ܺϲ�,��������Ʒ����,���������Ʒ��һ��
//	OutputID = ObjectIndex;
//	//������˫��
//	OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
//	//ִ�кϳ����ί��
//	CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
//	//ִ�ж�����Ʒί��
//	ThrowObject.ExecuteIfBound(InputID, InputNum);
//
//}
