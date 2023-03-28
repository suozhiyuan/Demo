// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/DemoType.h"
#include "DemoPlayerAnim.generated.h"


class UAnimMontage;
/**
 *
 */
UCLASS()
class DEMO_API UDemoPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDemoPlayerAnim();

	// ��Ӧ��ͼ�е� Event Blueprint Update Animation
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//�����͹ر�������Ʒ�Ľ������
	UFUNCTION(BlueprintCallable, Category = "Demo")
		void ChangeDetection(bool IsOpen);

	//�����͹ر�������Ʒ����ʾ���,�ڼ�����ʱ�����
	UFUNCTION(BlueprintCallable, Category = PlayAnim)
		void RenderHandObject(bool IsRender);

//	//���궫��ʱ����
//	UFUNCTION(BlueprintCallable, Category = PlayAnim)
//		void EatUpEvent();
//
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		float Speed;													// �ٶ�

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayAnim)
		FRotator SpineRotator;											// ��ת


protected:

	//��ȡ��ɫָ��
	void InitSPCharacter();

	//�������Ը�����ͼ����
	virtual void UpdateParameter();

	//���¶���
	virtual void UpdateMontage();

	//�޸��Ƿ������л��ӽ�
	void AllowViewChange(bool IsAllow);


protected:


	//��ɫָ��
	class ADemoPlayerCharacter* SPCharacter;

	//�ϰ����Montage
	UAnimMontage* PlayerHitMontage;			// ���
	UAnimMontage* PlayerFightMontage;		// �ӽ�
	UAnimMontage* PlayerPunchMontage;		// ȭ��
	UAnimMontage* PlayerEatMontage;			// �Զ���
	UAnimMontage* PlayerPickUpMontage;		// ʰȡ

	//���浱ǰ���ŵ�Montage
	UAnimMontage* CurrentMontage;

	//ָ���Լ��������˳�
	EGameViewMode::Type GameView;
};
