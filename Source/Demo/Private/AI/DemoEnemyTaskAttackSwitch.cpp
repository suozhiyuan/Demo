// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackSwitch.h"
//
//
//EBTNodeResult::Type UDemoEnemyTaskAttackSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
//	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
//	//�����ָ�븳ֵ
//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, SEController->GetPlayerPawn());
//	//�������Ѿ�����
//	if (SEController->IsPlayerDead())
//	{
//		//���߿�������ʧ�����
//		SEController->LoosePlayer();
//		//�޸�״̬ΪѲ��
//		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
//		//��������״̬
//		return EBTNodeResult::Failed;
//	}
//	//��ȡ����ҵľ���
//	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());
//	//�������С��200
//	if (EPDistance < 200.f)
//	{
//		//�޸Ĺ���״̬Ϊ�չ�
//		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Normal);
//		return EBTNodeResult::Succeeded;
//	}
//	//�������С��300�����ж��������Զ��
//	if (EPDistance < 300.f && SEController->IsPlayerAway())
//	{
//		//�޸�״̬Ϊ׷�𹥻�
//		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Pursuit);
//		return EBTNodeResult::Succeeded;
//	}
//	if (EPDistance > 200.f && EPDistance < 300.f)
//	{
//		//�޸Ĺ���״̬Ϊ���
//		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttackType.SelectedKeyName, (uint8)EEnemyAttackType::EA_Dash);
//		return EBTNodeResult::Succeeded;
//	}
//	//�������300
//	if (EPDistance > 300.f)
//	{
//		//�޸Ĺ���״̬Ϊ׷��
//		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Chase);
//		//��������״̬
//		return EBTNodeResult::Failed;
//	}
//	return EBTNodeResult::Failed;
//}
