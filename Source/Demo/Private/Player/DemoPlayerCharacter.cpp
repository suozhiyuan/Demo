// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Data/DemoType.h"
#include "Components/CapsuleComponent.h"
#include "Flob/DemoFlobObject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hand/DemoHandObject.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPackageManager.h"
#include "Player/DemoPlayerController.h"
#include "Player/DemoPlayerState.h"


// Sets default values
ADemoPlayerCharacter::ADemoPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//开始设置人物碰撞体的属性为PlayerProfile,下面的骨骼模型的碰撞就都可以设置为无碰撞
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));

	//添加第一人称骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());							// 关联到哪个组件上，这里可以是 RootComponent
	MeshFirst->bOnlyOwnerSee = true;																// 如果该值为True，则该组件仅在视图参与者是该组件的直接或间接所有者时才可见。
	MeshFirst->bCastDynamicShadow = false;															// 是否投射影子
	MeshFirst->bReceivesDecals = false;																// 是否接受贴花
	// 更新频率
	MeshFirst->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;		// 影响性能的参数，动画刷新的频率
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;													// 刷新顺序，参数为刷新组
	// 设置碰撞属性
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	// 设置位移
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// 获取第一人称的动作蓝图  创建蓝图对象用 FClassFinder，路径名后边需要加 _C
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;

	//给默认Mesh添加骨骼模型  创建 UObject 对象用 FObjectFinder
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);												// 将 骨骼模型 赋到 Mesh
	GetMesh()->bOnlyOwnerSee = true;																// 如果该值为True，则该组件仅在视图参与者是该组件的直接或间接所有者时才可见。
	GetMesh()->bReceivesDecals = false;																// 是否接受贴花
	GetMesh()->SetCollisionObjectType(ECC_Pawn);												// 在骨架网格上设置碰撞对象类型
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);							// 启用碰撞类型
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);										// 响应碰撞通道
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));							// 位置移动（相对）
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));		// 角度旋转（相对）

	//获取第三人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;

	//摄像机摇杆 创建普通对象，如Component对象用 CreateDefaultSubobject
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);										// 链接到哪个组件
	CameraBoom->TargetArmLength = 300.f;											// 设置距离
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);					// 设置偏移
	CameraBoom->bUsePawnControlRotation = true;										// 绑定Controller的旋转

	//初始化第三人称摄像机
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);		// 这里为啥要加 USpringArmComponent::SocketName  ？？？
	ThirdCamera->bUsePawnControlRotation = false;									// 设置 ThirdCamera 不跟随控制器的旋转

	//初始化第一人称摄像机
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FirstCamera->bUsePawnControlRotation = true;									// 设置跟随Controller的旋转
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));		// 设置偏移 

	//默认第三人称
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);

	//不显示第一人称模型
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

	//实例化手上物品
	HandObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("HandObject"));

	//加载死亡动画资源
	AnimDead = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/Player_Death.Player_Death'")));

	//初始化参数
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//设置初始速度为150.f
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	//初始为第三人称
	GameView = EGameViewMode::Third;

	//上半身动作初始为无动作
	UpperType = EUpperBody::None;

	//一开始允许切换视角
	IsAllowSwitch = true;

	//一开始输入不锁住输入
	IsInputLocked = false;

	//初始化没有攻击
	IsAttack = false;
}

// Called when the game starts or when spawned
void ADemoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//如果控制器指针为空,添加引用
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//把手持物品组件绑定到第三人称模型右手插槽上
	HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));

	//添加Actor到HandObject，游戏一开始默认就是空物体
	HandObject->SetChildActorClass(ADemoHandObject::SpawnHandObject(0));
}

// Called every frame
void ADemoPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADemoPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForWard", this, &ADemoPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ADemoPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADemoPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ADemoPlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADemoPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADemoPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ADemoPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ADemoPlayerCharacter::OnStopRun);
}

void ADemoPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView = NewGameView;
	switch (GameView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);					// 第一人称 Mesh 的显示
		GetMesh()->SetOwnerNoSee(true);						// 第三人称 Mesh 
		// 修改 handobject 绑定的位置到第一人称 Mesh
		HandObject->AttachToComponent(MeshFirst, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		// 修改 handobject 绑定的位置到第三人称 Mesh
		HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	}
}

void ADemoPlayerCharacter::ChangeHandObject(TSubclassOf<AActor> HandObjectClass)
{
	//设置物品到 HandObject
	HandObject->SetChildActorClass(HandObjectClass);
}

void ADemoPlayerCharacter::ChangeHandObjectDetect(bool IsOpen)
{
	//获取手上物品
	ADemoHandObject* HandObjectClass = Cast<ADemoHandObject>(HandObject->GetChildActor());
	if (HandObjectClass) HandObjectClass->ChangeOverlayDetect(IsOpen);

	//修改攻击状态
	IsAttack = IsOpen;
}

//是否渲染手上物品,由Anim进行调用
void ADemoPlayerCharacter::RenderHandObject(bool IsRender)
{
	//如果手上物品木有
	if (!HandObject->GetChildActor()) return;

	//如果有物品
	HandObject->GetChildActor()->SetActorHiddenInGame(!IsRender);		// SetActorHiddenInGame   隐藏
}

void ADemoPlayerCharacter::PlayerThrowObject(int ObjectID, int Num)
{
	if (GetWorld()) 
	{
		for (int i = 0; i < Num; ++i) 
		{
			//生成掉落资源
			ADemoFlobObject* FlobObject = GetWorld()->SpawnActor<ADemoFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 50.f), FRotator::ZeroRotator);

			//以丢弃方式生成掉落物
			FlobObject->ThrowFlobObject(ObjectID, GetActorRotation().Yaw);
		}
	}
}

bool ADemoPlayerCharacter::IsPackageFree(int ObjectID)
{
	return DemoPackageManager::Get()->SearchFreeSpace(ObjectID);
}

void ADemoPlayerCharacter::AddPackageObject(int ObjectID)
{
	DemoPackageManager::Get()->AddObject(ObjectID);
}

void ADemoPlayerCharacter::EatUpEvent()
{
	//如果玩家用户状态为空,直接返回
	if (!SPController->SPState) return;
	//告诉背包哪个快捷栏吃了东西,如果成功吃掉东西
	if (DemoPackageManager::Get()->EatUpEvent(SPController->SPState->CurrentShortcutIndex))
	{
		//告诉玩家状态类提升饥饿值
		SPController->SPState->PromoteHunger();
	}
}

bool ADemoPlayerCharacter::IsPlayerDead()
{
	if (SPController->SPState) return SPController->SPState->IsPlayerDead();
	return false;
}

void ADemoPlayerCharacter::AcceptDamage(int DamageVal)
{
	if (SPController->SPState) SPController->SPState->AcceptDamage(DamageVal);
}

FVector ADemoPlayerCharacter::GetCameraPos()
{
	switch (GameView)
	{
	case EGameViewMode::First:
		return FirstCamera->K2_GetComponentLocation();
	case EGameViewMode::Third:
		return ThirdCamera->K2_GetComponentLocation();
	}
	return FirstCamera->K2_GetComponentLocation();
}

float ADemoPlayerCharacter::PlayDeadAnim()
{
	GetMesh()->PlayAnimation(AnimDead, false);
	return AnimDead->GetMaxCurrentTime();
}

void ADemoPlayerCharacter::MoveForward(float Value)
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	if (Value != 0.f && Controller) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADemoPlayerCharacter::MoveRight(float Value)
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	if (Value != 0) 
	{
		const FQuat Rotation = GetActorQuat();
		FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ADemoPlayerCharacter::LookUpAtRate(float Value)
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADemoPlayerCharacter::Turn(float Value)
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	AddControllerYawInput(Value);
}

void ADemoPlayerCharacter::TurnAtRate(float Value)
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADemoPlayerCharacter::OnStartJump()
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	bPressedJump = true;
}

void ADemoPlayerCharacter::OnStopJump()
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	bPressedJump = false;
	StopJumping();
}

void ADemoPlayerCharacter::OnStartRun()
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	GetCharacterMovement()->MaxWalkSpeed = 375.f;
}

void ADemoPlayerCharacter::OnStopRun()
{
	//如果操作被锁住,直接返回
	if (IsInputLocked) return;

	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}