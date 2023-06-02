// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerAnim.h"

#include "Player/DemoPlayerCharacter.h"

UDemoPlayerAnim::UDemoPlayerAnim()
{

	Speed = 0.f;
	SpineRotator = FRotator(0.f, 0.f, 0.f);

}

void UDemoPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//��ʼ����ɫָ��
	InitSPCharacter();

	//������ͼ����
	UpdateParameter();

	//���¶���
	UpdateMontage();

}

void UDemoPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!SPCharacter) return;
	SPCharacter->ChangeHandObjectDetect(IsOpen);
}

void UDemoPlayerAnim::RenderHandObject(bool IsRender)
{
	if (!SPCharacter) return;
	SPCharacter->RenderHandObject(IsRender);
}

void UDemoPlayerAnim::EatUpEvent()
{
	if (!SPCharacter) return;

	//���߽�ɫ�ҳ��궫����
	SPCharacter->EatUpEvent();
}

void UDemoPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter) SPCharacter = Cast<ADemoPlayerCharacter>(TryGetPawnOwner());
}

void UDemoPlayerAnim::UpdateParameter()
{
	//���������ֱ�ӷ���,�����ָ������ж�
	if (!SPCharacter) return;

	//�����ٶ�
	Speed = SPCharacter->GetVelocity().Size();

	//�����ϰ������ת��ŷ���Ǻ�����ϵ����ת��
	float SpineDir = SPCharacter->GetActorRotation().Yaw - 90.f;			// SpineDir ������ĳ���
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void UDemoPlayerAnim::UpdateMontage()
{
	//���������ֱ�ӷ���,�����ָ������ж�
	if (!SPCharacter) return;

	//�����ǰ���˳�״̬����������Ĳ�һ��,ֱ�ӷ���
	if (SPCharacter->GameView != GameView) return;

	//�����ǰ�Ķ���û��ֹͣ,�����¶�����������갴��̧����������CurrentMontage
	if (!Montage_GetIsStopped(CurrentMontage)) return;

	switch (SPCharacter->UpperType)
	{
	case EUpperBody::None:
		//������ĸ������ڲ���
		if (CurrentMontage != nullptr) 
		{
			Montage_Stop(0);
			CurrentMontage = nullptr;
			//�����л��ӽ�
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:				// ȭ��
		if (!Montage_IsPlaying(PlayerPunchMontage)) 
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:				// 
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:				// �ӽ�
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:			// ʰȡ
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:				// ��
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	}
}

void UDemoPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacter) return;
	SPCharacter->IsAllowSwitch = IsAllow;
}