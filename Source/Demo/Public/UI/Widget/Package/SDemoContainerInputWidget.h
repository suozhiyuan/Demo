// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/Package/SDemoContainerBaseWidget.h"

/**
 * 
 */
class DEMO_API SDemoContainerInputWidget : public SDemoContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoContainerInputWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
