// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyTaskRotate.h"

#include "Enemy/DemoEnemyCharacter.h"
#include "Enemy/DemoEnemyController.h"

EBTNodeResult::Type UDemoEnemyTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//�����ʼ�����˲������ɹ�,ֱ�ӷ���ʧ��
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	// ����Ҫ
	////��ȡ��ҵ����˵���������ȥY����
	//FVector SEToSP = FVector(SEController->GetPlayerLocation().X, SEController->GetPlayerLocation().Y, 0.f) - (SECharacter->GetActorLocation().X, SECharacter->GetActorLocation().Y, 0.f);
	//SEToSP.Normalize();
	////���ߵ����µĳ���
	//SECharacter->UpdateHPBarRotation(FRotationMatrix::MakeFromX(SEToSP).Rotator());

	return EBTNodeResult::Succeeded;

}
