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
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	//获取工作号
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

	//初始化时物品数量和序号都为0
	ObjectIndex = ObjectNum = 0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SDemoContainerBaseWidget> SDemoContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SDemoContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SDemoContainerOutputWidget).WorkIndex(WorkID);		// 通过调用子类的 WorkIndex，将子类的 WorkIndex 传递给父类，给父类的 WorkIndex 赋值
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
	//如果鼠标移动到上面了
	if (IsHovered)
	{
		if (!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}
	else
	{
		if (IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	//更新当前状态
	IsHover = IsHovered;
}

void SDemoContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	//如果输入ID与上次不相同，更新贴图
	if (ObjectIndex != ObjectID) ObjectImage->SetBorderImage(DemoDataHandle::Get()->ObjectBrushList[ObjectID]);

	ObjectIndex = ObjectID;
	ObjectNum = Num;

	//如果物品ID为0
	if (ObjectIndex == 0) 
	{
		ObjectNumText->SetText(FText::FromString(""));
	}
	else
	{
		//判断物品是否可以叠加,是的话显示数量
		if (MultiplyAble(ObjectIndex)) 
		{
			//显示数量
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else
		{
			//不可叠加的话不显示数量
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
	//如果输入物品与容器本地物品相同并且可以叠加
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))		// 鼠标上的物品与容器相同，并且可以叠加
	{
		//根据数量判断 点击后返回的ID，64为放置上限，如果小于64则所有物品都放置到了容器内。如果大于64个，则鼠标上还存在物品
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;

		//如果小于64,返回0, 大于则返回差值
		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);

		//设置本地数量,上限为64
		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;

		//更新属性
		ResetContainerPara(ObjectIndex, ObjectNum);
		//直接返回
		return;
	}

	//如果输入物品与本地物品不相同，则直接更换数据
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	//更新容器中物品属性
	ResetContainerPara(InputID, InputNum);
}

void SDemoContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果输入为空,直接把本地的一半给出去
	if (InputID == 0)
	{
		// 将当前容器上的物品ID，给到鼠标上
		OutputID = ObjectIndex;			

		//区分单数双数，如果物品的数量是单数则鼠标上将拿到一半多1个
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);

		//更新容器中物品属性，如果减去给出去后的数量等于0则没有东西了
		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);

		return;
	}

	//如本地物品为空则添加一个到本地，或者物品相同并且物品可以合并
	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		//根据本地数量是否超出范围绑定输出数量，如果少等于64则鼠标上减一个物品，无果大于则数量不变
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;

		//根据数量是否为0定义输出ID
		OutputID = (OutputNum == 0) ? 0 : InputID;

		//更新容器中物品属性
		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);

		//直接返回
		return;
	}

	//如果物品不相同或者相同但是不能合并,直接交换
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;

	//更新属性
	ResetContainerPara(InputID, InputNum);
}

//bool SDemoContainerBaseWidget::IsEmpty()
//{
//	return ObjectIndex == 0;
//}
//
////不检测是否为空的情况,为空的情况由上方的方法检测
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
	//获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectID);

	//返回是否是武器或者工具
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}