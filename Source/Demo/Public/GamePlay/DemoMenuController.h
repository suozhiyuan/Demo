// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoMenuController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoMenuController : public APlayerController
{
	GENERATED_BODY()

	ADemoMenuController();
protected:

	virtual void BeginPlay() override;
};
