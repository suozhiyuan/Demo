// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
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

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//绑定到UIScaler的方法
	float GetUIScaler() const;

	//显示游戏UI,被PlayerController的ShowGameUI委托绑定
	void ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI);

public:
	//快捷栏指针
	TSharedPtr<class SDemoShortcutWidget> ShortcutWidget;

	//射线信息框
	TSharedPtr<class SDemoRayInfoWidget> RayInfoWidget;

	//准星
	TSharedPtr<class SDemoPointerWidget> PointerWidget;

	//玩家状态指针
	TSharedPtr<class SDemoPlayerStateWidget> PlayerStateWidget;

	//小地图引用
	TSharedPtr<class SDemoMiniMapWidget> MiniMapWidget;

	//聊天显示栏
	TSharedPtr<class SDemoChatShowWidget> ChatShowWidget;

	//游戏菜单
	TSharedPtr<class SDemoGameMenuWidget> GameMenuWidget;

	//聊天室
	TSharedPtr<class SDemoChatRoomWidget> ChatRoomWidget;

	//背包
	TSharedPtr<class SDemoPackageWidget> PackageWidget;

private:

	//获取屏幕Size
	FVector2D GetViewportSize() const;

	//将UI绑定到UIMap
	void InitUIMap();

private:

	//DPI缩放
	TAttribute<float> UIScaler;

	//黑色遮罩
	TSharedPtr<class SBorder> BlackShade;

	//UIMap
	TMap<EGameUIType::Type, TSharedPtr<SCompoundWidget>> UIMap;

	//消息计时器
	float MessageTimeCount;

};
