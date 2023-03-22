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
	 * ����Ϸ��������֮ǰ�ͻ����� UGameInstance �µ� Init
	 *
	 * ˳��GameMode��Init�������¼�����
	 */
	//virtual void Init() override;			

	UPROPERTY(VisibleAnywhere, Category = "Dame")
		FString GameName;

};
