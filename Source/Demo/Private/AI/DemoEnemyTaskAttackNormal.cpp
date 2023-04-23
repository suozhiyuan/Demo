// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackNormal.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"


EBTNodeResult::Type UDemoEnemyTaskAttackNormal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//播放普通攻击动画
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Normal);

	//设置参数
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	//返回成功
	return EBTNodeResult::Succeeded;
}
