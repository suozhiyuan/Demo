// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DemoPlayerAnim.h"
#include "DemoThirdPlayerAnim.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoThirdPlayerAnim : public UDemoPlayerAnim
{
	GENERATED_BODY()

public:

	UDemoThirdPlayerAnim();


protected:

	//重写更新属性方法
	virtual void UpdateParameter() override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;														// 是否在空中

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;													// 方向

};
