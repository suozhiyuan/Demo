// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class DEMO_API SDemoPackageWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoPackageWidget)
	{}
	SLATE_ATTRIBUTE(float, UIScaler)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//��д���ƺ���
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	//��д������¼�
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	//ע�ᱳ���������¼�,��playercharacter��InitPackageManagerί�н��е���
	void InitPackageManager();

private:

	//��ȡMenuStyle
	const struct FDemoGameStyle* GameStyle;


	//��������
	TSharedPtr<class SUniformGridPanel> ShortcutGrid;

	//�������
	TSharedPtr<SUniformGridPanel> PackageGrid;

	//�ϳɱ���
	TSharedPtr<SUniformGridPanel> CompoundGrid;

	//�������
	TSharedPtr<class SBorder> OutputBorder;

	//���λ�ñ궨
	FVector2D MousePosition;

	//DPI������
	TAttribute<float> UIScaler;

	//�Ƿ��Ѿ���ʼ������������
	bool IsInitPackageMana;

};
