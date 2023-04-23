// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskHurt.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskHurt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
	//播放受伤动画
	float ActionDuration = SECharacter->PlayHurtAction();
	//设置等待时间
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, ActionDuration);
	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskHurt::OnAnimationTimerDone);
	//注册到事件管理器
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, ActionDuration, false);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskHurt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活,直接返回
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;
	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	//返回
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskHurt::OnAnimationTimerDone()
{
	//告诉控制器受伤完成
	SEController->FinishStateHurt();
}
