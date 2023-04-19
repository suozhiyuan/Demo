// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskBase.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


bool UDemoEnemyTaskBase::InitEnemyElement(UBehaviorTreeComponent& OwnerComp)
{
	//����Ѿ���ʼ����,ֱ��return,�����ظ�����
	if (SEController && SECharacter) return true;

	//���и�ֵ
	SEController = Cast<ADemoEnemyController>(OwnerComp.GetAIOwner());
	if (SEController) 
	{
		SECharacter = Cast<ADemoEnemyCharacter>(SEController->GetPawn());
		if (SECharacter) return true;
	}

	return false;
}
