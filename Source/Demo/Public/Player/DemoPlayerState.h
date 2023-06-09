// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/DemoType.h"
#include "DemoPlayerState.generated.h"


//更新玩家状态UI委托
DECLARE_DELEGATE_TwoParams(FUpdateStateWidget, float, float)

/**
 *
 */
UCLASS()
class DEMO_API ADemoPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADemoPlayerState();

	virtual void Tick(float DeltaSeconds) override;

	//提供给 ShortcutWidget 的添加快捷栏容器委托
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);

	//切换快捷栏
	void ChooseShortcut(bool IsPre);

	//获取选中容器内的物品的Index
	int GetCurrentHandObjectIndex() const;

	//获取当前手持物品的物品类型
	EObjectType::Type GetCurrentObjectType();

	//提供给RayInfowidget的注册射线信息事件
	void RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock);

	//获取手上物品的攻击范围
	int GetAffectRange();

	//获取伤害值
	int GetDamageValue(EResourceType::Type ResourceType);

	//更改快捷栏物品信息
	void ChangeHandObject(int ShortcutID, int ObjectID, int ObjectNum);

	//提升饥饿值
	void PromoteHunger();

	//是否已经死亡
	bool IsPlayerDead();

	//接受伤害
	void AcceptDamage(int DamageVal);

	//加载血量和饥饿度
	void LoadState(float HPVal, float HungerVal);

	//保存血量和饥饿值到指定数据
	void SaveState(float& HPVal, float& HungerVal);


public:
	//当前被选中的快捷栏序号
	int CurrentShortcutIndex;

	//射线检测信息Text,由PlayerController进行更新
	FText RayInfoText;

	//更新玩家状态UI,绑定的方法是PlayerStateWidget的UpdateStateWidget
	FUpdateStateWidget UpdateStateWidget;

	//获取控制器指针
	class ADemoPlayerController* SPController;

protected:

	virtual void BeginPlay() override;


private:
	//获取快捷栏物品信息
	FText GetShortcutInfoText() const;

	//获取射线检测信息
	FText GetRayInfoText() const;

private:

	//快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	//快捷栏信息参数. TAttribute 绑定的函数，函数返回来的值修改时，自己同时也会修改
	TAttribute<FText> ShortcutInfoTextAttr;

	//射线信息参数
	TAttribute<FText> RayInfoTextAttr;

	//血值饥饿度
	float HP;
	float Hunger;

	//是否已经死亡
	bool IsDead;

};
