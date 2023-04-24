// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "GameFramework/Character.h"
#include "DemoPlayerCharacter.generated.h"

UCLASS()
class DEMO_API ADemoPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//修改视角
	void ChangeView(EGameViewMode::Type NewGameView);

	//修改当前的手持物品
	void ChangeHandObject(TSubclassOf<AActor> HandObjectClass);

	//修改手持物品的碰撞检测是否开启
	void ChangeHandObjectDetect(bool IsOpen);

	//是否渲染手上物品,由Anim进行调用
	void RenderHandObject(bool IsRender);

	//丢弃物品
	void PlayerThrowObject(int ObjectID, int Num);

	//背包是否有空间
	bool IsPackageFree(int ObjectID);

	//添加物品到背包
	void AddPackageObject(int ObjectID);

	//吃完东西调用的事件,由Anim进行调用
	void EatUpEvent();

	//获取是否已经死亡
	bool IsPlayerDead();

	//接受伤害
	void AcceptDamage(int DamageVal);

	//获取摄像机位置
	FVector GetCameraPos();

	////播放死亡动画,返回播放时长
	//float PlayDeadAnim();
public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
		class USpringArmComponent* CameraBoom;			// 摄像机摇杆

	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
		class UCameraComponent* ThirdCamera;			// 第三人称摄像机

	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
		UCameraComponent* FirstCamera;					// 第一人称摄像机

	//玩家控制器指针
	class ADemoPlayerController* SPController;

	//当前的视角模式
	EGameViewMode::Type GameView;

	//上半身动画状态
	EUpperBody::Type UpperType;

	//是否允许切换视角
	bool IsAllowSwitch;

	//是否锁住输入
	bool IsInputLocked;

	//是否在攻击
	bool IsAttack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAtRate(float Value);
	void Turn(float Value);
	void TurnAtRate(float Value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();


private:

	//第一人称的骨骼模型
	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
		USkeletalMeshComponent* MeshFirst;

	//手上物品
	UPROPERTY(VisibleDefaultsOnly, Category = "Demo")
		class UChildActorComponent* HandObject;

	// 旋转速度
	float BaseLookUpRate;
	float BaseTurnRate;

	////死亡动画资源
	//class UAnimationAsset* AnimDead;
};
