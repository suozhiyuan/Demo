// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/DemoType.h"
#include "DemoEnemyAnim.generated.h"


/**
 *
 */
UCLASS()
class DEMO_API UDemoEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UDemoEnemyAnim();

	// 重写帧动画更新
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//设置Idle模式,返回动作时长
	float SetIdelType(int NewType);

	//播放攻击动画,返回动画时长
	float PlayAttackAction(EEnemyAttackType AttackType);

	//播放受伤动画返回动画时长
	float PlayHurtAction();

	//停止所有动画
	void StopAllAction();

	//开启和关闭交互动作时的碰撞检测
	UFUNCTION(BlueprintCallable, Category = EnemyAnim)
		void ChangeDetection(bool IsOpen);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float IdleType;

	// 根骨骼的位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		FVector RootBonePos;

	// 根骨骼的权重
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float RootBoneAlpha;

	// 是否防御
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		bool IsDefence;


protected:

	//保存角色
	class ADemoEnemyCharacter* SECharacter;

	// 等待动作指针
	UAnimSequence* AnimIdle_I;
	UAnimSequence* AnimIdle_II;
	UAnimSequence* AnimIdle_III;

	// 攻击动画指针
	UAnimMontage* AnimAttack_I;
	UAnimMontage* AnimAttack_II;
	UAnimMontage* AnimAttack_III;
	UAnimMontage* AnimAttack_IV;

	// 攻击三与攻击四最原始的动作资源
	UAnimSequence* AnimAttackSeq_III;
	UAnimSequence* AnimAttackSeq_IV;

	//受伤动画指针
	UAnimMontage* AnimHurt;

	// 动作计时器
	float CurrentPlayTime;

	//动作第一帧Y轴位置
	float StartYPos;
};
