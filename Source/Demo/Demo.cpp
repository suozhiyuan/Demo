// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "UI/Style/DemoStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Demo, "Demo");

void FDemoModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

	//��ʼ����ʽ
	FSlateStyleRegistry::UnRegisterSlateStyle(DemoStyle::GetStyleSetName());

	DemoStyle::Initialze();		
}

void FDemoModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();

	DemoStyle::ShutDown();		// ע��
}
