// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandWood.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandWood : public ADemoHandObject
{
	GENERATED_BODY()

public:

	ADemoHandWood();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
