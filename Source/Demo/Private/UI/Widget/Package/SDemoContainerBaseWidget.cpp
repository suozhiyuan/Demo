// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SDemoContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Widget/Package/SDemoContainerInputWidget.h"
#include "UI/Widget/Package/SDemoContainerNormalWidget.h"
#include "UI/Widget/Package/SDemoContainerOutputWidget.h"
#include "UI/Widget/Package/SDemoContainerShortcutWidget.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoContainerBaseWidget::Construct(const FArguments& InArgs)
{
	//��ȡGameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	//��ȡ������
	WorkIndex = InArgs._WorkIndex;


	ChildSlot
		[
			SAssignNew(ContainerBorder, SBorder)
			.BorderImage(&GameStyle->NormalContainerBrush)
			.Padding(FMargin(8.f))
			[
				SAssignNew(ObjectImage, SBorder)
				.BorderImage(&GameStyle->EmptyBrush)
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Bottom)
				.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
				[
					SAssignNew(ObjectNumText, STextBlock)
					.Font(GameStyle->Font_Outline_16)
					.ColorAndOpacity(GameStyle->FontColor_Black)
				]
			]
		];


	IsHover = false;

	//��ʼ��ʱ��Ʒ��������Ŷ�Ϊ0
	ObjectIndex = ObjectNum = 0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SDemoContainerBaseWidget> SDemoContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SDemoContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SDemoContainerOutputWidget).WorkIndex(WorkID);		// ͨ����������� WorkIndex��������� WorkIndex ���ݸ����࣬������� WorkIndex ��ֵ
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer, SDemoContainerInputWidget).WorkIndex(WorkID);		
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer, SDemoContainerNormalWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer, SDemoContainerShortcutWidget).WorkIndex(WorkID);
		break;
	}
	return ResultContainer;
}

void SDemoContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	//�������ƶ���������
	if (IsHovered)
	{
		if (!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}
	else
	{
		if (IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	//���µ�ǰ״̬
	IsHover = IsHovered;
}

void SDemoContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	//�������ID���ϴβ���ͬ��������ͼ
	if (ObjectIndex != ObjectID) ObjectImage->SetBorderImage(DemoDataHandle::Get()->ObjectBrushList[ObjectID]);

	ObjectIndex = ObjectID;
	ObjectNum = Num;

	//�����ƷIDΪ0
	if (ObjectIndex == 0) 
	{
		ObjectNumText->SetText(FText::FromString(""));
	}
	else
	{
		//�ж���Ʒ�Ƿ���Ե���,�ǵĻ���ʾ����
		if (MultiplyAble(ObjectIndex)) 
		{
			//��ʾ����
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else
		{
			//���ɵ��ӵĻ�����ʾ����
			ObjectNumText->SetText(FText::FromString(""));
		}
	}
}

int SDemoContainerBaseWidget::GetIndex() const
{
	return ObjectIndex;
}

int SDemoContainerBaseWidget::GetNum() const
{
	return ObjectNum;
}

void SDemoContainerBaseWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//���������Ʒ������������Ʒ��ͬ���ҿ��Ե���
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))		// ����ϵ���Ʒ��������ͬ�����ҿ��Ե���
	{
		//���������ж� ����󷵻ص�ID��64Ϊ�������ޣ����С��64��������Ʒ�����õ��������ڡ��������64����������ϻ�������Ʒ
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;

		//���С��64,����0, �����򷵻ز�ֵ
		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);

		//���ñ�������,����Ϊ64
		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;

		//��������
		ResetContainerPara(ObjectIndex, ObjectNum);
		//ֱ�ӷ���
		return;
	}

	//���������Ʒ�뱾����Ʒ����ͬ����ֱ�Ӹ�������
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	//������������Ʒ����
	ResetContainerPara(InputID, InputNum);
}

void SDemoContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//�������Ϊ��,ֱ�Ӱѱ��ص�һ�����ȥ
	if (InputID == 0)
	{
		// ����ǰ�����ϵ���ƷID�����������
		OutputID = ObjectIndex;			

		//���ֵ���˫���������Ʒ�������ǵ���������Ͻ��õ�һ���1��
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

		//������������Ʒ���ԣ������ȥ����ȥ�����������0��û�ж�����
		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);

		return;
	}

	//�籾����ƷΪ�������һ�������أ�������Ʒ��ͬ������Ʒ���Ժϲ�
	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		//���ݱ��������Ƿ񳬳���Χ���������������ٵ���64������ϼ�һ����Ʒ���޹���������������
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;

		//���������Ƿ�Ϊ0�������ID
		OutputID = (OutputNum == 0) ? 0 : InputID;

		//������������Ʒ����
		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);

		//ֱ�ӷ���
		return;
	}

	//�����Ʒ����ͬ������ͬ���ǲ��ܺϲ�,ֱ�ӽ���
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	//��������
	ResetContainerPara(InputID, InputNum);
}

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

bool SDemoContainerBaseWidget::MultiplyAble(int ObjectID)
{
	//��ȡ��Ʒ����
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectID);

	//�����Ƿ����������߹���
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}