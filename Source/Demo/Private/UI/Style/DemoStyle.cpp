// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/DemoStyle.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"


void DemoStyle::Initialze()
{
	if (!DemoStyleInstance.IsValid()) 
	{
		DemoStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*DemoStyleInstance);
	}
}

FName DemoStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DemoStyle"));
	return StyleSetName;

}

void DemoStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*DemoStyleInstance);
	ensure(DemoStyleInstance.IsUnique());		// 如果这是对该对象的唯一共享引用，则返回true
	DemoStyleInstance.Reset();
}

const ISlateStyle& DemoStyle::Get()
{
	return *DemoStyleInstance;
}

TSharedRef<class FSlateStyleSet> DemoStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(DemoStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Roboto-Regular.ttf", 50));
	return StyleRef;
}