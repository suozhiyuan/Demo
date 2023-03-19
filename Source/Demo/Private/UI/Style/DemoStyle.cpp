// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/DemoStyle.h"
#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> DemoStyle::DemoStyleInstance = NULL;					// 如果是单例，变量不能放到构造函数

void DemoStyle::Initialze()
{
	if (!DemoStyleInstance.IsValid()) 
	{
		DemoStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*DemoStyleInstance);			// 注册进系统里边
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
	ensure(DemoStyleInstance.IsUnique());								// 如果这是对该对象的唯一共享引用，则返回true
	DemoStyleInstance.Reset();
}

const ISlateStyle& DemoStyle::Get()
{
	return *DemoStyleInstance;
}

TSharedRef<class FSlateStyleSet> DemoStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(DemoStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");		// FSlateGameResources 创建游戏资源
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Roboto-Regular.ttf", 50));	// FSlateFontInfo   Slate中字体的表示形式。
	return StyleRef;
}