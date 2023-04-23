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
	// ��дִ�к���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//��д������ֹ����
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	//�����������¼�
	void OnAnimationTimerDone();

protected:
	// �����Ƿ����
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector IsDefenceFinish;

	// ���ָ��
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector PlayerPawn;

	//���������������ί��
	FTimerHandle TimerHandle;
};
