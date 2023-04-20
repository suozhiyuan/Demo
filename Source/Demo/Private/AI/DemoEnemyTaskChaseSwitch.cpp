// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskChaseSwitch.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskChaseSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//��ȡ����ҵľ���
	float EPDistnce = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());

	//�������С��300��,״̬����Ϊ����,����׷��״̬
	if (EPDistnce < 300.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Attack);
		return EBTNodeResult::Failed;
	}

	//�������1500��,����Ѳ��״̬,��������û���������
	if (EPDistnce > 1500.f)
	{
		//���߿�������ʧ�����
		SEController->LoosePlayer();

		//�޸�״̬ΪѲ��
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);

		//����׷��״̬
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
}
