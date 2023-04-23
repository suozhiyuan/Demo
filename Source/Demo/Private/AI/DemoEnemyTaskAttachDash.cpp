// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttachDash.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskAttachDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//播放冲锋动画，返回动画时间
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Dash);

	//范围
	const float ChaseRadius = 5.f;

	//获取玩家到敌人之间的单位向量
	FVector SPToSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
	SPToSE.Normalize();

	//探索起点是玩家位置减去与敌人之间距离的一点点
	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 20.f * SPToSE;

	//保存随机的位置
	FVector DesLoc(0.f);

	//使用导航系统获取随机点
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);

	//计算一个机器人速度
	float Speed = (FVector::Distance(SECharacter->GetActorLocation(), DesLoc)) / AttackDuration + 30.f;

	//修改机器人速度
	SECharacter->SetMaxSpeed(Speed);

	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	//设置参数
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskAttachDash::OnAnimationTimerDone);
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);		//注册到事件管理器

	//继续执行
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskAttachDash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活,直接返回
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;

	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	//返回
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskAttachDash::OnAnimationTimerDone()
{
	//重新设置速度为300
	if (SECharacter) SECharacter->SetMaxSpeed(300.f);
}
