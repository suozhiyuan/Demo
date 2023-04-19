// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DemoBTDecoratorBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoBTDecoratorBase : public UBTDecorator
{
	GENERATED_BODY()

	//��Ӧ�ľ�����ͼ�ڵ�� PerformConditionCheck
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
