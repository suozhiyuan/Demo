// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "UI/Style/DemoStyle.h"

//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Demo, "Demo");

void FDemoModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();		// 创建后插件自动生成的

	//初始化样式
	FSlateStyleRegistry::UnRegisterSlateStyle(DemoStyle::GetStyleSetName());	// 先取消注册，避免重复注册
	DemoStyle::Initialze();		
}

void FDemoModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();		// 创建后插件自动生成的

	DemoStyle::ShutDown();		// 注销
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDemoModule, Demo, "Demo");