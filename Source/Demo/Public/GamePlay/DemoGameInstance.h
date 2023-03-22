// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/**
	 * 在游戏世界运行之前就会运行 UGameInstance 下的 Init
	 *
	 * 顺序：GameMode、Init、生成事件……
	 */
	//virtual void Init() override;			

	UPROPERTY(VisibleAnywhere, Category = "Dame")
		FString GameName;

};
