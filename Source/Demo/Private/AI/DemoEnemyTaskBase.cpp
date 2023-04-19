// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskBase.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


bool UDemoEnemyTaskBase::InitEnemyElement(UBehaviorTreeComponent& OwnerComp)
{
	//如果已经初始化了,直接return,避免重复调用
	if (SEController && SECharacter) return true;

	//进行赋值
	SEController = Cast<ADemoEnemyController>(OwnerComp.GetAIOwner());
	if (SEController) 
	{
		SECharacter = Cast<ADemoEnemyCharacter>(SEController->GetPawn());
		if (SECharacter) return true;
	}

	return false;
}
