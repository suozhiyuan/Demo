// Fill out your copyright notice in the De7scription page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DEMO_API SDemoMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//��UIScaler�ĺ���
	float GetUIScaler() const;

	//��ȡ��Ļ�ߴ�
	FVector2D GetViewportSize() const;

	///*
	// * Reply��һ��Slate�¼����ظ�ϵͳ�Ķ�����֪ͨ��һ���¼�����δ���ġ�
	// * ���磬һ��С�������ܻᴦ��һ��OnlouseDown�¼���Ҫ��ϵͳ��һ���ض���С������겶��
	// * Ϊ�ˣ�����FReply::CaptureMouse (NewMouseCapture)
	// */
	//FReply OnClick();		


private:
	//��ȡMenu��ʽ
	const struct FDemoMenuStyle* MenuStyle;

	//DPI����ϵ��
	TAttribute<float> UIScaler;

	//�˵�ָ��
	TSharedPtr<class SDemoMenuWidget> MenuWidget;

	//// ��ȡImage��Slot ��������޸�, �������Ҫ��Ҫ�޸ĵ� + SOverlay::Slot() �½��� .Expose(ImageSlot)
	//SOverlay::FOverlaySlot* ImageSlot;
};
