// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackNormal.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"


EBTNodeResult::Type UDemoEnemyTaskAttackNormal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//������ͨ��������
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Normal);

	//���ò���
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	//���سɹ�
	return EBTNodeResult::Succeeded;
}
