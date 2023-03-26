// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandApple.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandApple : public ADemoHandObject
{
	GENERATED_BODY()

public:

	ADemoHandApple();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
