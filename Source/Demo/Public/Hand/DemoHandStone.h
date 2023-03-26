// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandStone.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandStone : public ADemoHandObject
{
	GENERATED_BODY()
public:

	ADemoHandStone();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
