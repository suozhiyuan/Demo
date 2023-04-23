// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskRotate.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	// 不需要
	////获取玩家到敌人的向量，除去Y向量
	//FVector SEToSP = FVector(SEController->GetPlayerLocation().X, SEController->GetPlayerLocation().Y, 0.f) - (SECharacter->GetActorLocation().X, SECharacter->GetActorLocation().Y, 0.f);
	//SEToSP.Normalize();
	////告诉敌人新的朝向
	//SECharacter->UpdateHPBarRotation(FRotationMatrix::MakeFromX(SEToSP).Rotator());

	return EBTNodeResult::Succeeded;

}
