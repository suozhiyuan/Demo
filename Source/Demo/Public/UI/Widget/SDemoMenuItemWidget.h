// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"


DECLARE_DELEGATE_OneParam(FItemClicked, const EMenuItem::Type)		// ����1����������û�з��ص�ί�У����е�һ������Ϊί�������ڶ�������Ϊ����Ĳ���

/**
 * 
 */
class DEMO_API SDemoMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText, ItemText)				// ʹ�ô˺��widget�������н��������������ԣ����Կ�����ֵ����
	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)
	SLATE_EVENT(FItemClicked, OnClicked)			// ʹ�ô˺꽫������ӵ�widget���¼������widgetҪ��һ��ί�У�����1 ί����������2 �����¼�
	

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	//��д����� OnMouseButtonDown ����
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//��д��ť�����ķ���
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//����뿪
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;


private:
	//��ȡ��ɫ
	FSlateColor GetTintColor() const;

private:

	//��ȡMenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//�����¼�ί��
	FItemClicked OnClicked;

	//���水ť����
	EMenuItem::Type ItemType;

	//��ť�Ƿ��Ѿ�����
	bool IsMouseButtonDown;
};
