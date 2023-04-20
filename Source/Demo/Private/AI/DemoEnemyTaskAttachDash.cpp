// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskAttachDash.h"

//
//EBTNodeResult::Type UDemoEnemyTaskAttackDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
//	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
//
//	//����ͻ������
//	float AttackDuration = SECharacter->PlayAttackAction(EEnemyAttackType::EA_Dash);
//	//��Χ��0
//	const float ChaseRadius = 5.f;
//	//��ȡ��ҵ�����֮��ĵ�λ����
//	FVector SPToSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();
//	SPToSE.Normalize();
//	//̽����������λ�ü�ȥ�����֮������һ���
//	const FVector ChaseOrigin = SEController->GetPlayerLocation() - 20.f * SPToSE;
//	//���������λ��
//	FVector DesLoc(0.f);
//	//ʹ�õ���ϵͳ��ȡ�����
//	UNavigationSystem::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);
//	//��ɫ�ٶ�
//	float Speed = (FVector::Distance(SECharacter->GetActorLocation(), DesLoc)) / AttackDuration + 30.f;
//	//�޸ĵ����ٶ�
//	SECharacter->SetMaxSpeed(Speed);
//	//�޸�Ŀ�ĵ�
//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);
//	//���ò���
//	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, AttackDuration);
//	//����¼�ί��
//	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UDemoEnemyTaskAttackDash::OnAnimationTimerDone);
//	//ע�ᵽ�¼�������
//	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, AttackDuration, false);
//	//����ִ��
//	return EBTNodeResult::Succeeded;
//}
//
//EBTNodeResult::Type UDemoEnemyTaskAttackDash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	//�����ʼ�����˲������ɹ������¼����û�м���,ֱ�ӷ���
//	if (!InitEnemyElement(OwnerComp) || !TimerHandle.IsValid()) return EBTNodeResult::Aborted;
//	//ж��ʱ��ί��
//	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
//	//����
//	return EBTNodeResult::Aborted;
//}
//
//void UDemoEnemyTaskAttackDash::OnAnimationTimerDone()
//{
//	//���������ٶ�Ϊ300
//	if (SECharacter) SECharacter->SetMaxSpeed(300.f);
//}
