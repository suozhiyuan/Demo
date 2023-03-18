// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/DemoMenuWidgetStyle.h"

FDemoMenuStyle::FDemoMenuStyle()
{
}

FDemoMenuStyle::~FDemoMenuStyle()
{
}

const FName FDemoMenuStyle::TypeName(TEXT("FDemoMenuStyle"));

const FDemoMenuStyle& FDemoMenuStyle::GetDefault()
{
	static FDemoMenuStyle Default;
	return Default;
}

void FDemoMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

