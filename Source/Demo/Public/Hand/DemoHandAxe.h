// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandAxe.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandAxe : public ADemoHandObject
{
	GENERATED_BODY()
public:

	ADemoHandAxe();

protected:

	virtual void BeginPlay() override;
};
