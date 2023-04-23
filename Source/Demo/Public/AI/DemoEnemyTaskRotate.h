// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DemoEnemyTaskBase.h"
#include "DemoEnemyTaskRotate.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyTaskRotate : public UDemoEnemyTaskBase
{
	GENERATED_BODY()

	//ÖØÐ´Ö´ÐÐº¯Êý
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
