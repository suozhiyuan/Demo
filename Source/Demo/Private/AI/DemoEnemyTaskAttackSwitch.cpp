// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackSwitch.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskAttackSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//给玩家指针赋值
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, SEController->GetPlayerPawn());

	//如果玩家已经死亡
	if (SEController->IsPlayerDead())
	{
		//告诉控制器丢失了玩家
		SEController->LoosePlayer();

		//修改状态为巡逻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);

		//跳出攻击状态
		return EBTNodeResult::Failed;
	}

	//获取与玩家的距离
	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());		// Distance 获取两个坐标距离

	//如果距离小于200
	if (EPDistance < 200.f)
	{
		//修改攻击状态为普攻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Normal);
		return EBTNodeResult::Succeeded;		// Succeeded 成功结束，执行节点右边的任务
	}

	//如果距离小于300并且判定到玩家在远离
	if (EPDistance < 300.f && SEController->IsPlayerAway())
	{
		//修改状态为追逐攻击
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Pursuit);
		return EBTNodeResult::Succeeded;
	}

	if (EPDistance > 200.f && EPDistance < 300.f)
	{
		//修改攻击状态为冲刺
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Dash);
		return EBTNodeResult::Succeeded;
	}

	if (EPDistance > 300.f)
	{
		//修改攻击状态为追逐
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Chase);
		//跳出攻击状态
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
