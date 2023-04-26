// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

enum class ECultureTeam : uint8;

//存档委托
DECLARE_DELEGATE(FSaveGameDelegate)
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

	//失败方法
	void GameLose();

	//重置菜单
	void ResetMenu();

public:
	//存档委托,绑定GameMode的SaveGame函数
	FSaveGameDelegate SaveGameDele;

private:
	void InitializeWidget();

	FReply OptionEvent();		// 设置
	FReply SaveGameEvent();		// 保存
	FReply QuitGameEvent();		// 退出
	FReply GoBackEvent();		// 返回主菜单

	//改变语言
	void ChangeCulture(ECultureTeam Cultrue);
	//改变音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	
private:
	TSharedPtr<SBox> RootBox;

	TSharedPtr<SVerticalBox> VertBox;

	TSharedPtr<SButton> SaveGameButton;

	TSharedPtr<STextBlock> SaveGameText;

	TSharedPtr<SButton> QuitGameButton;

	TArray<TSharedPtr<SCompoundWidget>> MenuItemList;

	TArray<TSharedPtr<SCompoundWidget>> OptionItemList;

	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;
};
