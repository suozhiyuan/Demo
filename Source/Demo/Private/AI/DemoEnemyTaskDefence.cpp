// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskDefence.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskDefence::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//���ŷ�������
	SECharacter->StartDefence();

	//����û�н���״̬
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsDefenceFinish.SelectedKeyName, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName, SEController->GetPlayerPawn());

	//����¼�ί��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskDefence::OnAnimationTimerDone);
	//ע�ᵽ�¼�������,ѭ������Ƿ���Խ�������״̬
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.f, false);		

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskDefence::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ������¼����û�м���,ֱ�ӷ���
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;

	//ж��ʱ��ί��
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	//����
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskDefence::OnAnimationTimerDone()
{
	if (SEController) SEController->FinishStateDefence();
}
