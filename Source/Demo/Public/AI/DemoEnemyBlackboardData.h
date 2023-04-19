// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "DemoEnemyBlackboardData.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoEnemyBlackboardData : public UBlackboardData
{
	GENERATED_BODY()

public:

	virtual void PostLoad() override;

};
