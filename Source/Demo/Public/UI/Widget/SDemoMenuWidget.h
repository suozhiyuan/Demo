// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "Widgets/SCompoundWidget.h"


class SDemoChooseRecordWidget;
class SDemoNewGameWidget;
class SDemoGameOptionWidget;
struct MenuGroup;
	
/**
 *
 */
class DEMO_API SDemoMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//��дtick����
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;


private:

	//�󶨵�����MenuItem�ķ���
	void MenuItemOnClicked(EMenuItem::Type ItemType);

	//�޸�����
	void ChangeCulture(ECultureTeam Culture);

	//�޸�����
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

	//��ʼ�����еĿؼ�
	void InitializedMenuList();

	//����ѡ����ʾ�Ľ���
	void ChooseWidget(EMenuType::Type WidgetType);

	//�޸Ĳ˵��Ĵ�С
	void ResetWidgetSize(float NewWidget, float NewHeight);

	//��ʼ���������
	void InitializedAnimation();

	//���Źرն���
	void PlayClose(EMenuType::Type NewMenu);

//	//�˳���Ϸ
//	void QuitGame();

//	//������Ϸ
//	void EnterGame();


private:
	//��ȡMenuStyle
	const struct FDemoMenuStyle* MenuStyle;

	//����ĸ��ڵ�
	TSharedPtr<SBox> RootSizeBox;

	//�������
	TSharedPtr<STextBlock> TitleText;

	//�������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;

	//����˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;

	//��Ϸ����Widget������
	TSharedPtr<SDemoGameOptionWidget> GameOptionWidget;

	//����Ϸ�ؼ�ָ��
	TSharedPtr<SDemoNewGameWidget> NewGameWidget;

	//ѡ��浵�ؼ�ָ��
	TSharedPtr<SDemoChooseRecordWidget> ChooseRecordWidget;

	// �˵�����������
	FCurveSequence MenuAnimation;

	//�˵��������߿�����
	FCurveHandle MenuCurve;

	//���������µĸ߶�
	float CurrentHeight;

	//�Ƿ��Ѿ���ʾMenu���
	bool IsMenuShow;

	//�Ƿ���ס��ť
	bool ControlLocked;

	//���浱ǰ�Ķ���״̬
	EMenuAnim::Type AnimState;

	//���浱ǰ�Ĳ˵�
	EMenuType::Type CurrentMenu;
};
