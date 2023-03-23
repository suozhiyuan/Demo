// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DemoPlayerAnim.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UDemoPlayerAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

//	//开启和关闭手上物品的交互检测
//	UFUNCTION(BlueprintCallable, Category = "Demo")
//		void ChangeDetection(bool IsOpen);
//
//	//开启和关闭手上物品的显示与否,在捡东西的时候调用
//	UFUNCTION(BlueprintCallable, Category = PlayAnim)
//		void RenderHandObject(bool IsRender);
//
//	//吃完东西时调用
//	UFUNCTION(BlueprintCallable, Category = PlayAnim)
//		void EatUpEvent();
//
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;													// 速度

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;											// 旋转


protected:

	//获取角色指针
	void InitSPCharacter();

	//更新属性
	virtual void UpdateParameter();

//	//更新动作
//	virtual void UpdateMontage();
//
//	//修改是否允许切换视角
//	void AllowViewChange(bool IsAllow);
//
//
protected:


	//角色指针
	class ADemoPlayerCharacter* SPCharacter;
//
//	//上半身的Montage
//	UAnimMontage* PlayerHitMontage;
//	UAnimMontage* PlayerFightMontage;
//	UAnimMontage* PlayerPunchMontage;
//	UAnimMontage* PlayerEatMontage;
//	UAnimMontage* PlayerPickUpMontage;
//
//	//保存当前播放的Montage
//	UAnimMontage* CurrentMontage;
//
//	//指定自己的运行人称
//	EGameViewMode::Type GameView;
};
