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

	//��д�������Է���
	virtual void UpdateParameter() override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		bool IsInAir;														// �Ƿ��ڿ���

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Direction;													// ����

};
