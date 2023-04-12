// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class DEMO_API SDemoGameMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoGameMenuWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs);


//	//ʧ�ܷ���
//	void GameLose();
//
//	//���ò˵�
//	void ResetMenu();
//
//
//public:
//
//	//�浵ί��,��GameMode��SaveGame����
//	FSaveGameDelegate SaveGameDele;
//
//private:
//
//	void InitializeWidget();
//
//	FReply OptionEvent();
//	FReply SaveGameEvent();
//	FReply QuitGameEvent();
//	FReply GoBackEvent();
//
//	//�ı�����
//	void ChangeCulture(ECultureTeam Cultrue);
//	//�ı�����
//	void ChangeVolume(const float MusicVolume, const float SoundVolume);
//
//
//private:
//
//	TSharedPtr<class SBox> RootBox;
//
//	TSharedPtr<class SVerticalBox> VertBox;
//
//	TSharedPtr<SButton> SaveGameButton;
//
//	TSharedPtr<class STextBlock> SaveGameText;
//
//	TSharedPtr<class SButton> QuitGameButton;
//
//
//	TArray<TSharedPtr<SCompoundWidget>> MenuItemList;
//
//	TArray<TSharedPtr<SCompoundWidget>> OptionItemList;
//
//
//	//��ȡGameStyle
//	const struct FDemoGameStyle* GameStyle;
};
