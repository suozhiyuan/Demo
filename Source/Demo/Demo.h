// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// ģ�����ʱ���õķ���
class FDemoModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;		// ģ�����ʱ����
	virtual void ShutdownModule() override;		// ģ��ж��ʱ����

};