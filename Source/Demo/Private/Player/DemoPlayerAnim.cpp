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
	//初始化角色指针
	InitSPCharacter();

	//更新蓝图数据
	UpdateParameter();

	//更新动作
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

	//告诉角色我吃完东西了
	SPCharacter->EatUpEvent();
}

void UDemoPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter) SPCharacter = Cast<ADemoPlayerCharacter>(TryGetPawnOwner());
}

void UDemoPlayerAnim::UpdateParameter()
{
	//如果不存在直接返回,避免空指针产生中断
	if (!SPCharacter) return;

	//设置速度
	Speed = SPCharacter->GetVelocity().Size();

	//定义上半身的旋转，欧拉角和坐标系做了转换
	float SpineDir = SPCharacter->GetActorRotation().Yaw - 90.f;			// SpineDir 摄像机的朝向
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void UDemoPlayerAnim::UpdateMontage()
{
	//如果不存在直接返回,避免空指针产生中断
	if (!SPCharacter) return;

	//如果当前的人称状态和这个动作的不一致,直接返回
	if (SPCharacter->GameView != GameView) return;

	//如果当前的动作没有停止,不更新动作，避免鼠标按键抬起立即重置CurrentMontage
	if (!Montage_GetIsStopped(CurrentMontage)) return;

	switch (SPCharacter->UpperType)
	{
	case EUpperBody::None:
		//如果有哪个动作在播放
		if (CurrentMontage != nullptr) 
		{
			Montage_Stop(0);
			CurrentMontage = nullptr;
			//允许切换视角
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:				// 拳击
		if (!Montage_IsPlaying(PlayerPunchMontage)) 
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			//不允许切换视角
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:				// 
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			//不允许切换视角
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:				// 挥剑
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			//不允许切换视角
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:			// 拾取
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			//不允许切换视角
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:				// 吃
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			//不允许切换视角
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