// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskWander.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//溜达范围是1000
	const float WanderRadius = 1000.f;

	//溜达起点是自己的位置
	const FVector WanderOrigin = SECharacter->GetActorLocation();

	//保存随机的位置
	FVector DesLoc(0.f);

	//使用导航系统获取随机点，需要在构建配置中加入 NavigationSystem
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController, WanderOrigin, DesLoc, WanderRadius);

	//当距离小于500时,重新找点
	while (FVector::Distance(WanderOrigin, DesLoc) < 500.f)
	{
		//使用导航系统重新获取随机点
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController, WanderOrigin, DesLoc, WanderRadius);
	}

	//修改速度为100
	SECharacter->SetMaxSpeed(100.f);

	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	//获取停顿时长
	float TotalWaitTime = SECharacter->GetIdleWaitTime();

	//修改等待时长
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, TotalWaitTime);

	//返回成功
	return EBTNodeResult::Succeeded;
}
