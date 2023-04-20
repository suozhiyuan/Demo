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

	//目的地
	FBlackboardEntry Destination;
	Destination.EntryName = FName("Destination");
	UBlackboardKeyType_Vector* DestinationKeyType = NewObject<UBlackboardKeyType_Vector>();
	Destination.KeyType = DestinationKeyType;

	//敌人状态
	FBlackboardEntry EnemyState;
	EnemyState.EntryName = FName("EnemyState");
	UBlackboardKeyType_Enum* EnemyStateKeyType = NewObject<UBlackboardKeyType_Enum>();
	EnemyStateKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAIState"), true);		// 通过反射创建了一个 EEnemyAIState
	EnemyStateKeyType->EnumName = FString("EEnemyAIState");		// 创建一个 EnemyStateKeyType ，和上一句代码均可创建
	EnemyState.KeyType = EnemyStateKeyType;

	//等待时间
	FBlackboardEntry WaitTime;										// 黑板条目的定义
	WaitTime.EntryName = FName("WaitTime");							// 变量名
	WaitTime.KeyType = NewObject<UBlackboardKeyType_Float>();		// 变量类型

	//攻击类型
	FBlackboardEntry AttackType;
	AttackType.EntryName = FName("AttackType");
	UBlackboardKeyType_Enum* AttackTypeKeyType = NewObject<UBlackboardKeyType_Enum>();
	AttackTypeKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAttackType"), true);
	AttackTypeKeyType->EnumName = FString("EEnemyAttackType");
	AttackType.KeyType = AttackTypeKeyType;

	//玩家指针
	FBlackboardEntry PlayerPawn;
	PlayerPawn.EntryName = FName("PlayerPawn");
	UBlackboardKeyType_Object* PlayerPawnKeyType = NewObject<UBlackboardKeyType_Object>();
	PlayerPawnKeyType->BaseClass = ADemoPlayerCharacter::StaticClass();
	PlayerPawn.KeyType = PlayerPawnKeyType;

	//某一个动作是否完成
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
