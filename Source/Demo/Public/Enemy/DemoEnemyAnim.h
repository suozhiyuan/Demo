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

	// ��д֡��������
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//����Idleģʽ,���ض���ʱ��
	float SetIdelType(int NewType);

	//���Ź�������,���ض���ʱ��
	float PlayAttackAction(EEnemyAttackType AttackType);

	//�������˶������ض���ʱ��
	float PlayHurtAction();

	//ֹͣ���ж���
	void StopAllAction();

//	//�����͹رս�������ʱ����ײ���
//	UFUNCTION(BlueprintCallable, Category = EnemyAnim)
//		void ChangeDetection(bool IsOpen);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float IdleType;

	// ��������λ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		FVector RootBonePos;

	// ��������Ȩ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float RootBoneAlpha;

	// �Ƿ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		bool IsDefence;


protected:

	//�����ɫ
	class ADemoEnemyCharacter* SECharacter;

	// �ȴ�����ָ��
	UAnimSequence* AnimIdle_I;
	UAnimSequence* AnimIdle_II;
	UAnimSequence* AnimIdle_III;

	// ��������ָ��
	UAnimMontage* AnimAttack_I;
	UAnimMontage* AnimAttack_II;
	UAnimMontage* AnimAttack_III;
	UAnimMontage* AnimAttack_IV;

	// �������빥������ԭʼ�Ķ�����Դ
	UAnimSequence* AnimAttackSeq_III;
	UAnimSequence* AnimAttackSeq_IV;

	//���˶���ָ��
	UAnimMontage* AnimHurt;

	// ������ʱ��
	float CurrentPlayTime;

	//������һ֡Y��λ��
	float StartYPos;
};
