// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class DEMO_API SDemoPlayerStateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoPlayerStateWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//����״̬�¼�,�󶨵�ί����PlayerState��UpdateStateWidget
	void UpdateStateWidget(float HPValue, float HungerValue);

private:

	//��ȡGameStyle
	const struct FDemoGameStyle* GameStyle;

	//Ѫ��
	TSharedPtr<class SProgressBar> HPBar;

	//������
	TSharedPtr<SProgressBar> HungerBar;
};
