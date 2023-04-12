// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerBaseWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoContainerBaseWidget::Construct(const FArguments& InArgs)
{
	////��ȡGameStyle
	//GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");
	////��ȡ������
	//WorkIndex = InArgs._WorkIndex;


	//ChildSlot
	//	[
	//		SAssignNew(ContainerBorder, SBorder)
	//		.BorderImage(&GameStyle->NormalContainerBrush)
	//	.Padding(FMargin(8.f))
	//	[
	//		SAssignNew(ObjectImage, SBorder)
	//		.BorderImage(&GameStyle->EmptyBrush)
	//	.HAlign(HAlign_Right)
	//	.VAlign(VAlign_Bottom)
	//	.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
	//	[
	//		SAssignNew(ObjectNumText, STextBlock)
	//		.Font(GameStyle->Font_Outline_16)
	//	.ColorAndOpacity(GameStyle->FontColor_Black)
	//	]
	//	]
	//	];


	//IsHover = false;

	////��ʼ��ʱ��Ʒ��������Ŷ�Ϊ0
	//ObjectIndex = ObjectNum = 0;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//
//TSharedPtr<SDemoContainerBaseWidget> SDemoContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
//{
//	TSharedPtr<SDemoContainerBaseWidget> ResultContainer;
//	switch (NeedType)
//	{
//	case EContainerType::Output:
//		SAssignNew(ResultContainer, SDemoContainerOutputWidget).WorkIndex(WorkID);
//		break;
//	case EContainerType::Input:
//		SAssignNew(ResultContainer, SDemoContainerInputWidget).WorkIndex(WorkID);
//		break;
//	case EContainerType::Normal:
//		SAssignNew(ResultContainer, SDemoContainerNormalWidget).WorkIndex(WorkID);
//		break;
//	case EContainerType::Shortcut:
//		SAssignNew(ResultContainer, SDemoContainerShortcutWidget).WorkIndex(WorkID);
//		break;
//	}
//	return ResultContainer;
//}
//
//void SDemoContainerBaseWidget::UpdateHovered(bool IsHovered)
//{
//	//�������ƶ���������
//	if (IsHovered)
//	{
//		if (!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
//	}
//	else
//	{
//		if (IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
//	}
//	//���µ�ǰ״̬
//	IsHover = IsHovered;
//}
//
//void SDemoContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
//{
//	//�������ID����ͬ,������ͼ
//	if (ObjectIndex != ObjectID) ObjectImage->SetBorderImage(DemoDataHandle::Get()->ObjectBrushList[ObjectID]);
//
//	ObjectIndex = ObjectID;
//	ObjectNum = Num;
//
//	//�����ƷIDΪ0
//	if (ObjectIndex == 0) {
//		ObjectNumText->SetText(FText::FromString(""));
//	}
//	else
//	{
//		//�ж���Ʒ�Ƿ���Ե���,�ǵĻ���ʾ����
//		if (MultiplyAble(ObjectIndex)) {
//			//��ʾ����
//			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
//		}
//		else
//		{
//			//���ɵ��ӵĻ�����ʾ����
//			ObjectNumText->SetText(FText::FromString(""));
//		}
//	}
//}
//
//int SDemoContainerBaseWidget::GetIndex() const
//{
//	return ObjectIndex;
//}
//
//int SDemoContainerBaseWidget::GetNum() const
//{
//	return ObjectNum;
//}
//
//void SDemoContainerBaseWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
//{
//	//���������Ʒ�뱾����Ʒ��ͬ���ҿ��Ե���
//	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))
//	{
//		//���������жϷ��ص�ID
//		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;
//		//���С��64,����0, �����򷵻ز�ֵ
//		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);
//		//���ñ�������,����Ϊ64
//		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;
//		//��������
//		ResetContainerPara(ObjectIndex, ObjectNum);
//		//ֱ�ӷ���
//		return;
//	}
//
//	//ֱ�Ӹ�������
//	OutputID = ObjectIndex;
//	OutputNum = ObjectNum;
//	//��������
//	ResetContainerPara(InputID, InputNum);
//}
//
//void SDemoContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
//{
//	//�������Ϊ��,ֱ�Ӱѱ��ص�һ�����ȥ,ʹ�ý�һ��
//	if (InputID == 0)
//	{
//		OutputID = ObjectIndex;
//		//���ֵ���˫��
//		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
//		//��������
//		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
//		//ֱ�ӷ���
//		return;
//	}
//
//	//�����Ʒ��ͬ������Ʒ���Ժϲ�  ���߱�����ƷΪ��,���һ��������
//	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
//	{
//		//���ݱ��������Ƿ񳬳���Χ���������
//		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;
//		//���������Ƿ�Ϊ0�������ID
//		OutputID = (OutputNum == 0) ? 0 : InputID;
//		//��������
//		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);
//		//ֱ�ӷ���
//		return;
//	}
//
//	//�����Ʒ����ͬ������ͬ���ǲ��ܺϲ�,ֱ�ӽ���
//	OutputID = ObjectIndex;
//	OutputNum = ObjectNum;
//	//��������
//	ResetContainerPara(InputID, InputNum);
//
//}
//
//bool SDemoContainerBaseWidget::IsEmpty()
//{
//	return ObjectIndex == 0;
//}
//
////������Ƿ�Ϊ�յ����,Ϊ�յ�������Ϸ��ķ������
//bool SDemoContainerBaseWidget::RemainSpace(int ObjectID)
//{
//	if (ObjectIndex == ObjectID && ObjectNum < 64 && MultiplyAble(ObjectIndex)) return true;
//	return false;
//}
//
//void SDemoContainerBaseWidget::AddObject(int ObjectID)
//{
//	if (ObjectIndex == 0)
//	{
//		ResetContainerPara(ObjectID, 1);
//		return;
//	}
//	if (ObjectIndex == ObjectID && ObjectNum < 64 && MultiplyAble(ObjectIndex)) {
//		ResetContainerPara(ObjectIndex, ObjectNum + 1);
//	}
//}
//
//bool SDemoContainerBaseWidget::MultiplyAble(int ObjectID)
//{
//	//��ȡ��Ʒ����
//	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
//	//�����Ƿ����������߹���
//	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
//}