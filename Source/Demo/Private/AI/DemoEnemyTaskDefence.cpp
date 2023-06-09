// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskDefence.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskDefence::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//播放防御动画
	SECharacter->StartDefence();

	//设置没有结束状态
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsDefenceFinish.SelectedKeyName, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, SEController->GetPlayerPawn());

	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskDefence::OnAnimationTimerDone);
	//注册到事件管理器,循环检测是否可以进入其他状态
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);		

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskDefence::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活,直接返回
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;

	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	//返回
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskDefence::OnAnimationTimerDone()
{
	if (SEController) SEController->FinishStateDefence();
}
