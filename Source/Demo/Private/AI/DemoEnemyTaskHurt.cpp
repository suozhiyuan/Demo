// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskHurt.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskHurt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
	//�������˶���
	float ActionDuration = SECharacter->PlayHurtAction();
	//���õȴ�ʱ��
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, ActionDuration);
	//����¼�ί��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskHurt::OnAnimationTimerDone);
	//ע�ᵽ�¼�������
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, ActionDuration, false);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskHurt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ������¼����û�м���,ֱ�ӷ���
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;
	//ж��ʱ��ί��
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	//����
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskHurt::OnAnimationTimerDone()
{
	//���߿������������
	SEController->FinishStateHurt();
}
