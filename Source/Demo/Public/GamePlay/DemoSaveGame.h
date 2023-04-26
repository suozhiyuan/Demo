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
		FVector PlayerLocation;						// 玩家位置

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		float PlayerHP;								// 玩家血量

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		float PlayerHunger;							// 饥饿度

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> InputIndex;					// 合成表输入框内容ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> InputNum;						// 合成表输入框内容数量

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> NormalIndex;					// 背包主体的内容ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> NormalNum;					// 背包主体的内容数量

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> ShortcutIndex;				// 快捷栏的内容ID

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<int32> ShortcutNum;					// 快捷栏的内容数量

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> EnemyLoaction;				// 敌人位置

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<float> EnemyHP;						// 敌人血量

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> ResourceRock;				// 场景石头资源

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> ResourceTree;				// 场景树木资源

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> PickupStone;				// 可拾取的石头

	UPROPERTY(VisibleAnywhere, Category = "Demo")
		TArray<FVector> PickupWood;					// 可拾取的木头

};
