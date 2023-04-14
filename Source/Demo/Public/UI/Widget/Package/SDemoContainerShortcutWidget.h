// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/Package/SDemoContainerBaseWidget.h"

/**
 * 
 */
class DEMO_API SDemoContainerShortcutWidget : public SDemoContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoContainerShortcutWidget)
	{}
	SLATE_ATTRIBUTE(int, WorkIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void ResetContainerPara(int ObjectID, int Num) override;
};
