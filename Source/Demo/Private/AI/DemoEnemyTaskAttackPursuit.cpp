// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackPursuit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskAttackPursuit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//播放追击动画
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Pursuit);

	//设置速度为600,不小于玩家
	SECharacter->SetMaxSpeed(600.f);

	//设置参数
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsActionFinish.SelectedKeyName, false);

	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskAttackPursuit::OnAnimationTimerDone);
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);		//注册到事件管理器

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskAttackPursuit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活,直接返回
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;
	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	//返回
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskAttackPursuit::OnAnimationTimerDone()
{
	//设置动作完成
	if (SEController) SEController->ResetProcess(true);

	//修改速度回300
	if (SECharacter) SECharacter->SetMaxSpeed(300.f);
}
