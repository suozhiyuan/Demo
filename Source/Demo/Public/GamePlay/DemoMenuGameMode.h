// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	
	ADemoMenuGameMode();

protected:
	virtual void BeginPlay() override;
};
