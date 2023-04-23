// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DemoEnemyTaskBase.h"
#include "DemoEnemyTaskAttackSwitch.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyTaskAttackSwitch : public UDemoEnemyTaskBase
{
	GENERATED_BODY()
	//ÖØÐ´Ö´ÐÐº¯Êý
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector AttackType;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector EnemyState;

//	UPROPERTY(EditAnywhere, Category = "Blackboard")
//		struct FBlackboardKeySelector PlayerPawn;

};
