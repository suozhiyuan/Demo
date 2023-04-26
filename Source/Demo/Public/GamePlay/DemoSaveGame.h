// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DemoSaveGame.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API UDemoSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		FVector PlayerLocation;						// ���λ��

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		float PlayerHP;								// ���Ѫ��

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		float PlayerHunger;							// ������

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> InputIndex;					// �ϳɱ����������ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> InputNum;						// �ϳɱ��������������

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> NormalIndex;					// �������������ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> NormalNum;					// �����������������

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> ShortcutIndex;				// �����������ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> ShortcutNum;					// ���������������

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> EnemyLoaction;				// ����λ��

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<float> EnemyHP;						// ����Ѫ��

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> ResourceRock;				// ����ʯͷ��Դ

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> ResourceTree;				// ������ľ��Դ

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> PickupStone;				// ��ʰȡ��ʯͷ

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> PickupWood;					// ��ʰȡ��ľͷ

};
