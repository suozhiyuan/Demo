// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DemoEnemyBlackboardData.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Player/DemoPlayerCharacter.h"


void UDemoEnemyBlackboardData::PostLoad()
{
	Super::PostLoad();

	//Ŀ�ĵ�
	FBlackboardEntry Destination;
	Destination.EntryName = FName("Destination");
	UBlackboardKeyType_Vector* DestinationKeyType = NewObject<UBlackboardKeyType_Vector>();
	Destination.KeyType = DestinationKeyType;

	//����״̬
	FBlackboardEntry EnemyState;
	EnemyState.EntryName = FName("EnemyState");
	UBlackboardKeyType_Enum* EnemyStateKeyType = NewObject<UBlackboardKeyType_Enum>();
	EnemyStateKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAIState"), true);		// ͨ�����䴴����һ�� EEnemyAIState
	EnemyStateKeyType->EnumName = FString("EEnemyAIState");		// ����һ�� EnemyStateKeyType ������һ�������ɴ���
	EnemyState.KeyType = EnemyStateKeyType;

	//�ȴ�ʱ��
	FBlackboardEntry WaitTime;										// �ڰ���Ŀ�Ķ���
	WaitTime.EntryName = FName("WaitTime");							// ������
	WaitTime.KeyType = NewObject<UBlackboardKeyType_Float>();		// ��������

	//��������
	FBlackboardEntry AttackType;
	AttackType.EntryName = FName("AttackType");
	UBlackboardKeyType_Enum* AttackTypeKeyType = NewObject<UBlackboardKeyType_Enum>();
	AttackTypeKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAttackType"), true);
	AttackTypeKeyType->EnumName = FString("EEnemyAttackType");
	AttackType.KeyType = AttackTypeKeyType;

	//���ָ��
	FBlackboardEntry PlayerPawn;
	PlayerPawn.EntryName = FName("PlayerPawn");
	UBlackboardKeyType_Object* PlayerPawnKeyType = NewObject<UBlackboardKeyType_Object>();
	PlayerPawnKeyType->BaseClass = ADemoPlayerCharacter::StaticClass();
	PlayerPawn.KeyType = PlayerPawnKeyType;

	//ĳһ�������Ƿ����
	FBlackboardEntry ProcessFinish;
	ProcessFinish.EntryName = FName("ProcessFinish");
	ProcessFinish.KeyType = NewObject<UBlackboardKeyType_Bool>();


	Keys.Add(Destination);
	Keys.Add(EnemyState);
	Keys.Add(WaitTime);
	Keys.Add(AttackType);
	Keys.Add(PlayerPawn);
	Keys.Add(ProcessFinish);
}