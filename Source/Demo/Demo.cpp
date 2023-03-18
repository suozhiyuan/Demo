// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "UI/Style/DemoStyle.h"

//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Demo, "Demo");

void FDemoModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();		// ���������Զ����ɵ�

	//��ʼ����ʽ
	FSlateStyleRegistry::UnRegisterSlateStyle(DemoStyle::GetStyleSetName());	// ��ȡ��ע�ᣬ�����ظ�ע��
	DemoStyle::Initialze();		
}

void FDemoModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();		// ���������Զ����ɵ�

	DemoStyle::ShutDown();		// ע��
}

IMPLEMENT_PRIMARY_GAME_MODULE(FDemoModule, Demo, "Demo");