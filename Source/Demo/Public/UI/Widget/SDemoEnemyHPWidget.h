// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DEMO_API SDemoEnemyHPWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoEnemyHPWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//提供给敌人角色来调用
	void ChangeHP(float HP);

private:

	TSharedPtr<class SProgressBar> HPBar;

	//结果颜色
	FLinearColor ResultColor;
};
