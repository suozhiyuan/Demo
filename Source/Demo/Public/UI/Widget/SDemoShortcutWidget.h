// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


////ע��������PlayerState���ί��
//DECLARE_DELEGATE_TwoParams(FRegisterShortCutContainer, TArray<TSharedPtr<ShortcutContainer>>*, TSharedPtr<STextBlock>)

/**
*
*/
class DEMO_API SDemoShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

//public:
//
//	FRegisterShortCutContainer RegisterShortcutContainer;

private:

	//��ʼ����������
	void InitializeContainer();

private:

	//��ȡGameStyle
	const struct FDemoGameStyle* GameStyle;

	//��Ʒ��Ϣ��ָ��
	TSharedPtr<class STextBlock> ShortcutInfoTextBlock;

	//����ָ��
	TSharedPtr<class SUniformGridPanel> GridPanel;

	//�Ƿ��ʼ������
	bool IsInitializeContainer;

};
