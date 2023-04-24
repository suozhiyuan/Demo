// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DemoEnemyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Data/DemoDataHandle.h"
#include "Enemy/DemoEnemyAnim.h"
#include "Enemy/DemoEnemyController.h"
#include "EnemyTool/DemoEnemyTool.h"
#include "Flob/DemoFlobObject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Player/DemoPlayerCharacter.h"
#include "UI/Widget/SDemoEnemyHPWidget.h"


// Sets default values
ADemoEnemyCharacter::ADemoEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//设置AI控制器
	AIControllerClass = ADemoEnemyController::StaticClass();

	//设置碰撞体属性文件
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	//GetCapsuleComponent()->bGenerateOverlapEvents = true;		// 交互检测
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);		// 交互检测

	//添加模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'"));
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);		// 设置Mesh
	GetMesh()->SetCollisionObjectType(ECC_Pawn);		// 碰撞对象类型
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// 启用碰撞类型
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);				// 响应碰撞通道
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//添加动画蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Animation.Enemy_Animation_C'"));	   // 注意后边的 _C
	GetMesh()->AnimClass = StaticEnemyAnim.Class;

	//实例化插槽
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));
	SheildSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("SheildSocket"));

	//实例化血条
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->AttachTo(RootComponent);

	//实例化敌人感知组件
	EnemySense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("EnemySense"));

	//加载死亡动画资源
	AnimDead_I = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_I.Enemy_Dead_I'")));
	AnimDead_II = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_II.Enemy_Dead_II'")));

	////设置下一帧不销毁自己,得放在构造函数进行初始化,避免与GameMode的加载函数冲突
	//IsDestroyNextTick = false;
}

// Called when the game starts or when spawned
void ADemoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//获取动作引用
	SEAnim = Cast<UDemoEnemyAnim>(GetMesh()->GetAnimInstance());
	SEController = Cast<ADemoEnemyController>(GetController());

	//绑定插槽
	WeaponSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
	SheildSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LHSocket"));

	//给插槽添加物品
	WeaponSocket->SetChildActorClass(ADemoEnemyTool::SpawnEnemyWeapon());
	SheildSocket->SetChildActorClass(ADemoEnemyTool::SpawnEnemySheild());

	//设置血条widget
	SAssignNew(HPBarWidget, SDemoEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));
	//设置初始血量
	HP = 200.f;
	HPBarWidget->ChangeHP(HP / 200.f);

	//敌人感知参数设置
	EnemySense->HearingThreshold = 0.f;					// 不受遮挡时的听觉
	EnemySense->LOSHearingThreshold = 0.f;				// 
	EnemySense->SightRadius = 1000.f;					// 最大视野距离
	EnemySense->SetPeripheralVisionAngle(55.f);			// 最大视野角度
	EnemySense->bHearNoises = false;					// 是否可以听到声音

	//绑定看到玩家的方法
	FScriptDelegate OnSeePlayerDele;
	OnSeePlayerDele.BindUFunction(this, "OnSeePlayer");
	EnemySense->OnSeePawn.Add(OnSeePlayerDele);

	//设置资源ID是3
	ResourceIndex = 3;
}

//生成资掉落
void ADemoEnemyCharacter::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	//遍历生成
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It)
	{
		//随机流
		FRandomStream Stream;
		//产生新的随机种子
		Stream.GenerateNewSeed();
		//生成数量，数组的第2和第3个值
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld())
		{
			for (int i = 0; i < Num; ++i)
			{
				//生成掉落资源
				ADemoFlobObject* FlobObject = GetWorld()->SpawnActor<ADemoFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 40.f), FRotator::ZeroRotator);
				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

// Called every frame
void ADemoEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////如果准备销毁为true,进行销毁
	//if (IsDestroyNextTick) DestroyEvent();
}

// Called to bind functionality to input
void ADemoEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADemoEnemyCharacter::UpdateHPBarRotation(FVector SPLoaction)
{
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);						// 我的位置 看向敌人的方向
	FVector TargetPos(SPLoaction.X, SPLoaction.Y, 0.f);									// 目标位置
	HPBar->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}

void ADemoEnemyCharacter::SetMaxSpeed(float Speed)
{
	//设置最大运动速度
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float ADemoEnemyCharacter::GetIdleWaitTime()
{
	//如果动作蓝图不存在直接返回3秒
	if (!SEAnim) return 3.f;

	//创建随机流
	FRandomStream Stream;
	Stream.GenerateNewSeed();		// 生成一个新的随机种子
	int IdleTpye = Stream.RandRange(0, 2);
	float AnimLength = SEAnim->SetIdelType(IdleTpye);		// 通过随机数确定一个动作

	//更新种子
	Stream.GenerateNewSeed();

	//产生动作次数
	int AnimCount = Stream.RandRange(1, 3);

	//返回全部的动画时长
	return AnimLength * AnimCount;
}

float ADemoEnemyCharacter::PlayAttackAction(EEnemyAttackType AttackType)
{
	//如果动作蓝图不存在直接返回0秒
	if (!SEAnim) return 0.f;

	//返回攻击时长
	return SEAnim->PlayAttackAction(AttackType);
}

// 接受攻ji
void ADemoEnemyCharacter::AcceptDamage(int DamageVal)
{
	//如果开启了防御,直接返回
	if (SEAnim && SEAnim->IsDefence) return;

	//进行血值更新
	HP = FMath::Clamp<float>(HP - DamageVal, 0.f, 500.f);		
	HPBarWidget->ChangeHP(HP / 200.f);

	//如果血值小于0
	if (HP == 0.f && !DeadHandle.IsValid())			// DeadHandle.IsValid() 如果这个句柄曾经被计时器管理器初始化，则为True
	{
		//告诉控制器死亡，停止行为树
		SEController->EnemyDead();

		//停止所有动画
		SEAnim->StopAllAction();

		// 死亡定时器时间
		float DeadDuration = 0.f;

		// 随机数
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		int SelectIndex = Stream.RandRange(0, 1);

		if (SelectIndex == 0)
		{
			GetMesh()->PlayAnimation(AnimDead_I, false);			// 第二个参数：是否循环，不循环的话会一直停留在最后一帧
			DeadDuration = AnimDead_I->GetMaxCurrentTime() * 2;			// 获取执行时间,计算停留时间
		}
		else
		{
			GetMesh()->PlayAnimation(AnimDead_II, false);
			DeadDuration = AnimDead_II->GetMaxCurrentTime() * 2;
		}

		//生成掉落物
		CreateFlobObject();

		//添加事件委托
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ADemoEnemyCharacter::DestroyEvent);		// 绑定
		GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);		// 计时器
	}
	else
	{
		//告诉控制器收到伤害
		if (SEController) SEController->UpdateDamageRatio(HP / 200.f);
	}
}

float ADemoEnemyCharacter::PlayHurtAction()
{
	//如果动作蓝图不存在直接返回0秒
	if (!SEAnim) return 0.f;
	//返回攻击时长
	return SEAnim->PlayHurtAction();
}

void ADemoEnemyCharacter::StartDefence()
{
	if (SEAnim) SEAnim->IsDefence = true;
}

void ADemoEnemyCharacter::StopDefence()
{
	if (SEAnim) SEAnim->IsDefence = false;
}

void ADemoEnemyCharacter::DestroyEvent()
{
	//注销时间函数
	if (DeadHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(DeadHandle);

	//销毁自己
	GetWorld()->DestroyActor(this);
}

//FText ADemoEnemyCharacter::GetInfoText() const
//{
//	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
//	switch (DemoDataHandle::Get()->CurrentCulture)
//	{
//	case ECultureTeam::EN:
//		return ResourceAttr->EN;
//		break;
//	case ECultureTeam::ZH:
//		return ResourceAttr->ZH;
//		break;
//	}
//	return ResourceAttr->ZH;
//}
//
//void ADemoEnemyCharacter::ChangeWeaponDetect(bool IsOpen)
//{
//	//如果手持物品存在,修改检测
//	ADemoEnemyTool* WeaponClass = Cast<ADemoEnemyTool>(WeaponSocket->GetChildActor());
//	if (WeaponClass) WeaponClass->ChangeOverlayDetect(IsOpen);
//}
//
//bool ADemoEnemyCharacter::IsLockPlayer()
//{
//	if (SEController) return SEController->IsLockPlayer;
//	return false;
//}
//
//void ADemoEnemyCharacter::LoadHP(float HPVal)
//{
//	HP = HPVal;
//	//修改血量显示
//	HPBarWidget->ChangeHP(HP / 200.f);
//}
//
//float ADemoEnemyCharacter::GetHP()
//{
//	return HP;
//}

void ADemoEnemyCharacter::OnSeePlayer(APawn* PlayerChar)
{
	if (Cast<ADemoPlayerCharacter>(PlayerChar)) 
	{
		// 告诉控制器我看到玩家了
		if (SEController) SEController->OnSeePlayer();
	}
}