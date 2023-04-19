// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DemoEnemyTaskBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyTaskBase : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	//初始化控制器和角色,不成功就返回false
	bool InitEnemyElement(UBehaviorTreeComponent& OwnerComp);

protected:

	class ADemoEnemyController* SEController;

	class ADemoEnemyCharacter* SECharacter;
};
