// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// 模组加载时调用的方法
class FDemoModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;		// 模组加载时调用
	virtual void ShutdownModule() override;		// 模组卸载时调用

};