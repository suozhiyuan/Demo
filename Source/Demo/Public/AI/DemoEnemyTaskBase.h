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

	//��ʼ���������ͽ�ɫ,���ɹ��ͷ���false
	bool InitEnemyElement(UBehaviorTreeComponent& OwnerComp);

protected:

	class ADemoEnemyController* SEController;

	class ADemoEnemyCharacter* SECharacter;
};
