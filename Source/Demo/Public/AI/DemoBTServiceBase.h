// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DemoBTServiceBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UDemoBTServiceBase : public UBTService
{
	GENERATED_BODY()

protected:

	//按AI系统的特殊帧率进行更新,可以把数据更新放在这里
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
