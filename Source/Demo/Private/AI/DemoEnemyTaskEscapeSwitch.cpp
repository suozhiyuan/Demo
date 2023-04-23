// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskEscapeSwitch.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskEscapeSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//��ȡ����ҵľ���
	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());

	//�������1500��,�ص�Ѳ��״̬,��������û���������
	if (EPDistance > 1500.f) 
	{
		//���߿�������ʧ�����
		SEController->LoosePlayer();

		//�޸�״̬ΪѲ��
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
	}
	return EBTNodeResult::Succeeded;
}