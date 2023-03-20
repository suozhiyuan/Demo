// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSlider.h"

//�޸���Ӣ��ί��
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
//�޸�����ί��
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)


class DEMO_API SDemoGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoGameOptionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	//ͳһ������ʽ
	void StyleInitialize();

	//����CheckBox�¼�
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//Ӣ��CheckBox�¼�
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
	//�����仯�¼�
	//void MusicSliderChanged(float Value);
	//void SoundSliderChanged(float Value);

private:
	//��ȡMenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//��ȡCheckBoxָ��
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;

	//����������
	TSharedPtr<SSlider> MuSlider;//��������
	TSharedPtr<SSlider> SoSlider;//��Ч

	//�������ٷֱ�
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;

	//ί�б���
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;
};
