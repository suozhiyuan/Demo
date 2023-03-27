// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"



class SDemoShortcutWidget;
/**
 *
 */
class DEMO_API SDemoGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


	//virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//�󶨵�UIScaler�ķ���
	float GetUIScaler() const;

	////��ʾ��ϷUI,��PlayerController��ShowGameUIί�а�
	//void ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI);

public:
	//�����ָ��
	TSharedPtr<class SDemoShortcutWidget> ShortcutWidget;

	//������Ϣ��
	TSharedPtr<class SDemoRayInfoWidget> RayInfoWidget;

	//׼��
	TSharedPtr<class SDemoPointerWidget> PointerWidget;

//	//���״ָ̬��
//	TSharedPtr<class SDemoPlayerStateWidget> PlayerStateWidget;
//	//С��ͼ����
//	TSharedPtr<class SDemoMiniMapWidget> MiniMapWidget;
//	//������ʾ������
//	TSharedPtr<class SDemoChatShowWidget> ChatShowWidget;
//
//
//	//��Ϸ�˵�
//	TSharedPtr<class SDemoGameMenuWidget> GameMenuWidget;
//	//������
//	TSharedPtr<class SDemoChatRoomWidget> ChatRoomWidget;
//	//����
//	TSharedPtr<class SDemoPackageWidget> PackageWidget;
//
//
private:

	//��ȡ��ĻSize
	FVector2D GetViewportSize() const;

//	//��UI�󶨵�UIMap
//	void InitUIMap();
//
private:

	//DPI����
	TAttribute<float> UIScaler;

//	//��ɫ����
//	TSharedPtr<class SBorder> BlackShade;
//
//	//UIMap
//	TMap<EGameUIType::Type, TSharedPtr<SCompoundWidget>> UIMap;
//
//	//��Ϣ��ʱ��
//	float MessageTimeCount;

};
