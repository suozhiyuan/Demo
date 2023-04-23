// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DemoEnemyTaskBase.h"
#include "DemoEnemyTaskDefence.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyTaskDefence : public UDemoEnemyTaskBase
{
	GENERATED_BODY()
	// 重写执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//重写任务终止函数
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	//动作结束后事件
	void OnAnimationTimerDone();

protected:
	// 动作是否完成
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector IsDefenceFinish;

	// 玩家指针
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector PlayerPawn;

	//攻击动作结束后的委托
	FTimerHandle TimerHandle;
};
