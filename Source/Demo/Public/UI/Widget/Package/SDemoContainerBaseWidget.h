// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"

//�ϳ�����ί��
DECLARE_DELEGATE(FCompoundInput)
//�ϳ���ȡί��,��������Ʒ���, ��Ʒ����
DECLARE_DELEGATE_TwoParams(FCompoundOutput, int, int)
//������Ʒί��,��������Ʒ���, ��Ʒ����
DECLARE_DELEGATE_TwoParams(FThrowObject, int, int)
//�������������״̬������Ϸ�仯ί��, �����ֱ��ǿ�������, ���µ���ƷID, ������Ʒ����
DECLARE_DELEGATE_ThreeParams(FPackShortChange, int, int, int)

/**
 *
 */
class DEMO_API SDemoContainerBaseWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoContainerBaseWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)		// slate ����

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//��ȡʵ��
	static TSharedPtr<SDemoContainerBaseWidget> CreateContainer(EContainerType::Type NeedType, int WorkID);

	//��������ƶ��������״̬
	void UpdateHovered(bool IsHovered);

	//���ø��¸�������
	virtual void ResetContainerPara(int ObjectID, int Num);

	//��ȡ��������ƷID
	int GetIndex() const;
	//��ȡ��������Ʒ����
	int GetNum() const;

	/**
	 * @brief ����������
	 * @param InputID			��ǰ��������ŵ���ƷID
	 * @param InputNum			��ǰ��������ŵ���Ʒ����
	 * @param OutputID			�����֮����������ŵ���ƷID
	 * @param OutputNum			�����֮����������ŵ���Ʒ����
	 */
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);


	/**
	 * @brief 	�Ҽ��������
	 * @param InputID 
	 * @param InputNum 
	 * @param OutputID 
	 * @param OutputNum 
	 */
	virtual void RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum);

//	//�Ƿ�Ϊ��
//	bool IsEmpty();
//
//	//�Ƿ��пռ�
//	bool RemainSpace(int ObjectID);
//
//	//���һ��Ԫ��
//	void AddObject(int ObjectID);

public:
	//�ϳ�����ί��
	FCompoundInput CompoundInput;
	//�ϳ����ί��
	FCompoundOutput CompoundOutput;
	//������Ʒί��
	FThrowObject ThrowObject;
	//���������ί��
	FPackShortChange PackShortChange;

protected:
	//MultiplyAble
	//��ȡ�Ƿ���Ե���
	bool MultiplyAble(int ObjectID);

protected:
	//�����������
	TSharedPtr<class SBorder> ContainerBorder;		// ������
	TSharedPtr<SBorder> ObjectImage;				// ����ͼƬ
	TSharedPtr<class STextBlock> ObjectNumText;		// ��������

	//��ȡMenuStyle
	const struct FDemoGameStyle* GameStyle;

	//�������,���ڱ궨�ڱ����е�λ������
	TAttribute<int> WorkIndex;

	//�Ƿ���Hover״̬
	bool IsHover;

	//��Ʒ���
	int ObjectIndex;

	//��Ʒ����
	int ObjectNum;
};
