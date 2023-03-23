// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoThirdPlayerAnim.h"

#include "Common/DemoHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DemoPlayerCharacter.h"


UDemoThirdPlayerAnim::UDemoThirdPlayerAnim()
{
//
//	//����Դ��Montage
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
//	PlayerHitMontage = PlayerHitMon.Object;
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
//	PlayerEatMontage = PlayerEatMon.Object;
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
//	PlayerFightMontage = PlayerFightMon.Object;
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
//	PlayerPunchMontage = PlayerPunchMon.Object;
//	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
//	PlayerPickUpMontage = PlayerPickUpMon.Object;
//
//
//	//�����Լ��������˳��ǵ����˳�
//	GameView = EGameViewMode::Third;

	// ������ֵ
	Direction = 0.f;

	// ���Ƿ��ڿ��и�ֵ
	IsInAir = false;
}

void UDemoThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();

	//���������ֱ�ӷ���,�����ָ������ж�
	if (!SPCharacter) return;

	//��ȡ�Ƿ�����Ծ
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();

	// �ƶ��������ķ��� ��ȥ ��ɫ(�����)���򣬾������������ת��Եķ�������������������Ͽռ�
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

	// ���һ�����ݣ����һ��
	DemoHelper::Debug(FString("SPCharacter->GetVelocity: ") + FString::SanitizeFloat(SPCharacter->GetVelocity().ToOrientationRotator().Yaw), 0.f);
	DemoHelper::Debug(FString("SPCharacter: ") + FString::SanitizeFloat(SPCharacter->GetActorRotation().Yaw), 0.f);
	DemoHelper::Debug(FString("PreDir: ") + FString::SanitizeFloat(PreDir), 0.f);

	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;

	// ���һ�����ݣ����һ��
	DemoHelper::Debug(FString("Direction: ") + FString::SanitizeFloat(Direction), 0.f);
}
