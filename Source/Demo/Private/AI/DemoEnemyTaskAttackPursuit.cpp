// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttackPursuit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/DemoType.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"


EBTNodeResult::Type UDemoEnemyTaskAttackPursuit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//����׷������
	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Pursuit);

	//�����ٶ�Ϊ600,��С�����
	SECharacter->SetMaxSpeed(600.f);

	//���ò���
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsActionFinish.SelectedKeyName, false);

	//����¼�ί��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskAttackPursuit::OnAnimationTimerDone);
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);		//ע�ᵽ�¼�������

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UDemoEnemyTaskAttackPursuit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ������¼����û�м���,ֱ�ӷ���
	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;
	//ж��ʱ��ί��
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	//����
	return EBTNodeResult::Aborted;
}

void UDemoEnemyTaskAttackPursuit::OnAnimationTimerDone()
{
	//���ö������
	if (SEController) SEController->ResetProcess(true);

	//�޸��ٶȻ�300
	if (SECharacter) SECharacter->SetMaxSpeed(300.f);
}
