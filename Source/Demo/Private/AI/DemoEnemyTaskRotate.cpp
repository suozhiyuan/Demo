// Fill out your copyright notice in the Description page of Project Settings.
// 废弃

#include "AI/DemoEnemyTaskRotate.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
