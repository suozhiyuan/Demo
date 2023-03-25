// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/DemoGameWidgetStyle.h"

FDemoGameStyle::FDemoGameStyle()
{
}

FDemoGameStyle::~FDemoGameStyle()
{
}

const FName FDemoGameStyle::TypeName(TEXT("FDemoGameStyle"));

const FDemoGameStyle& FDemoGameStyle::GetDefault()
{
	static FDemoGameStyle Default;
	return Default;
}

void FDemoGameStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

