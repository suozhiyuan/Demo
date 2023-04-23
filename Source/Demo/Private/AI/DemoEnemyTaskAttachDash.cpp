// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttachDash.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskAttachDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//���ų�涯�������ض���ʱ��
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Dash);

	//��Χ
	const float ChaseRadius = 5.f;

	//��ȡ��ҵ�����֮��ĵ�λ����
	FVector SPToSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
	SPToSE.Normalize();

	//̽����������λ�ü�ȥ�����֮������һ���
	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 20.f * SPToSE;

	//���������λ��
	FVector DesLoc(0.f);

	//ʹ�õ���ϵͳ��ȡ�����
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);

	//����һ���������ٶ�
	float Speed = (FVector::Distance(SECharacter->GetActorLocation(), DesLoc)) / AttackDuration + 30.f;

	//�޸Ļ������ٶ�
	SECharacter->SetMaxSpeed(Speed);

	//�޸�Ŀ�ĵ�
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);

	//���ò���
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);

	//����¼�ί��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskAttachDash::OnAnimationTimerDone);
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);		//ע�ᵽ�¼�������

	//����ִ��
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskAttachDash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ������¼����û�м���,ֱ�ӷ���
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;

	//ж��ʱ��ί��
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	//����
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskAttachDash::OnAnimationTimerDone()
{
	//���������ٶ�Ϊ300
	if (SECharacter) SECharacter->SetMaxSpeed(300.f);
}
