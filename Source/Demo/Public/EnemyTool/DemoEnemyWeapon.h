// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTool/DemoEnemyTool.h"
#include "DemoEnemyWeapon.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API ADemoEnemyWeapon : public ADemoEnemyTool
{
	GENERATED_BODY()

public:

	ADemoEnemyWeapon();
	
	//protected:
	//
	//	UFUNCTION()
	//		virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
