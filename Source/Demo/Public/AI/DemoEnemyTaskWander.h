// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DemoEnemyTaskBase.h"
#include "DemoEnemyTaskWander.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyTaskWander : public UDemoEnemyTaskBase
{
	GENERATED_BODY()
	//��дִ�к���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	// Ŀ�ĵ�
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector Destination;

	//�޸ĵȴ�ʱ��
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector WaitTime;

};
