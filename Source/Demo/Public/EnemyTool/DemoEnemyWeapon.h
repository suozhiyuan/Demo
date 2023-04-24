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
	
protected:

	//UFUNCTION()			// 加 UFUNCTION() 编译生成会报错，但重新生成不会报错 父类(DemoEnemyTool)中的UFUNCTION的重写不能在其上面有UFUNCTION()声明;它将使用与原始声明相同的参数。
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
