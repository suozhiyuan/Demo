// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoEnemyHPWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoEnemyHPWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		// Populate the widget
		SAssignNew(HPBar, SProgressBar)
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoEnemyHPWidget::ChangeHP(float HP)
{
	HP = FMath::Clamp<float>(HP, 0.f, 1.f);						// HP 范围
	HPBar->SetPercent(HP);													// 设置百分比
	ResultColor = FLinearColor(1.f - HP, HP, 0.f, 1.f);		// 计算颜色
	HPBar->SetFillColorAndOpacity(FSlateColor(ResultColor));				// 设置颜色
}