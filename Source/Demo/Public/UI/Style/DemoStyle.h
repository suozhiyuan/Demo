// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO_API DemoStyle
{
public:
	static void Initialze();

	static FName GetStyleSetName();			// 获取样式名字

	static void ShutDown();					// 游戏关闭时调用，取消注册

	static const ISlateStyle& Get();		// 


private:
	static TSharedRef<class FSlateStyleSet> Create();		// FSlateStyleSet 一个石式块，包含外观的命名属性集合。
	static TSharedPtr<FSlateStyleSet> DemoStyleInstance;	// 

};
