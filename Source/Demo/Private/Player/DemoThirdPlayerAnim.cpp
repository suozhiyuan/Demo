// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoThirdPlayerAnim.h"

#include "Animation/AnimMontage.h"
#include "Common/DemoHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DemoPlayerCharacter.h"


UDemoThirdPlayerAnim::UDemoThirdPlayerAnim()
{
	//绑定资源到Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
	PlayerHitMontage = PlayerHitMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
	PlayerFightMontage = PlayerFightMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
	PlayerPunchMontage = PlayerPunchMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
	PlayerEatMontage = PlayerEatMon.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
	PlayerPickUpMontage = PlayerPickUpMon.Object;

	//设置自己的运行人称是第三人称
	GameView = EGameViewMode::Third;

	// 给方向赋值
	Direction = 0.f;

	// 给是否在空中赋值
	IsInAir = false;
}

void UDemoThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();

	//如果不存在直接返回,避免空指针产生中断
	if (!SPCharacter) return;

	//获取是否在跳跃
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();

	// 移动控制器的方向 减去 角色(摄像机)朝向，就是摄像机的旋转相对的方向，这个方向给到动作混合空间
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

	//// 输出一下数据，理解一下
	//DemoHelper::Debug(FString("SPCharacter->GetVelocity: ") + FString::SanitizeFloat(SPCharacter->GetVelocity().ToOrientationRotator().Yaw), 0.f);
	//DemoHelper::Debug(FString("SPCharacter: ") + FString::SanitizeFloat(SPCharacter->GetActorRotation().Yaw), 0.f);
	//DemoHelper::Debug(FString("PreDir: ") + FString::SanitizeFloat(PreDir), 0.f);

	// 混合空间中要使用 + -180度来做判断，所以要将大于180和小于-180的值进行转换
	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;

	//// 输出一下数据，理解一下
	//DemoHelper::Debug(FString("Direction: ") + FString::SanitizeFloat(Direction), 0.f);
}
