// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandMeat.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandMeat : public ADemoHandObject
{
	GENERATED_BODY()
public:

	ADemoHandMeat();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
