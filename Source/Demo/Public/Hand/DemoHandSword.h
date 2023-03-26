// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandSword.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandSword : public ADemoHandObject
{
	GENERATED_BODY()

public:

	ADemoHandSword();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
