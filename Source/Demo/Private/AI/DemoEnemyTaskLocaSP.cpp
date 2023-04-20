// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskLocaSP.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskLocaSP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//��Χ��20����
	const float ChaseRadius = 20.f;

	//��ȡ��ҵ�����֮��ĵ�λ����
	FVector SPToSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
	SPToSE.Normalize();		// ������������ڸ����Ĺ���������о͵ع�һ����������ǣ����ֲ��䡣

	// ̽����������λ�ü�ȥ�����֮������һ���
	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 100.f * SPToSE;

	//���������λ��
	FVector DesLoc(0.f);

	//ʹ�õ���ϵͳ��ȡ�����
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);

	//�޸�Ŀ�ĵ�
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	//�޸��ٶ�Ϊ300
	SECharacter->SetMaxSpeed(300.f);

	//���سɹ�
	return EBTNodeResult::Succeeded;
}
