// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/LineBatchComponent.h"
#include "Data/DemoType.h"
#include "Hand/DemoHandObject.h"
#include "Data/DemoDataHandle.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Pickup/DemoPickupObject.h"
#include "Player/DemoPlayerCharacter.h"
#include "Player/DemoPlayerState.h"
#include "Resource/DemoResourceObject.h"


ADemoPlayerController::ADemoPlayerController()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
}

void ADemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//获取角色与状态
	if (!SPCharacter) SPCharacter = Cast<ADemoPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ADemoPlayerState>(PlayerState);

	//设置鼠标不显示
	bShowMouseCursor = false;

	//设置输入模式， GameOnly 和 GameUI 可以互相转换，但如果转换成 UIOnly 便不能转换成其他输入模式
	FInputModeGameOnly InputMode;					// 用于设置只允许玩家输入/玩家控制器响应用户输入的输入模式的数据结构。
	InputMode.SetConsumeCaptureMouseDown(true);		// 是否捕获鼠标点击
	SetInputMode(InputMode);						// 设置输入模式

	//设置预动作
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	//初始化是否按住鼠标键
	IsLeftButtonDown = false;
	IsRightButtonDown = false;

	//设置默认UI状态为游戏界面
	CurrentUIType = EGameUIType::Game;

	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ADemoPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 临时代码
	ChangePreUpperType(EUpperBody::None);

	// 圆形进度条 测试代码
	//static float TestPointer = 1.f;
	//TestPointer = FMath::FInterpTo(TestPointer, 0, DeltaSeconds, 1.f);
	//UpdatePointer.ExecuteIfBound(true, FMath::Clamp(TestPointer, 0.f, 1.f));

	//进行射线检测
	RunRayCast();

	// 处理动作状态
	StateMachine();

	//处理小地图更新
	TickMiniMap();
}

void ADemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//绑定视角切换
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ADemoPlayerController::ChangeView);
	//绑定鼠标按下事件
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ADemoPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ADemoPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ADemoPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ADemoPlayerController::RightEventStop);

	//绑定鼠标滑轮事件
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ADemoPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ADemoPlayerController::ScrollDownEvent);

	//绑定ESC键事件并且设置当暂停游戏的时候依然可以运行
	InputComponent->BindAction("EscEvent", IE_Pressed, this, &ADemoPlayerController::EscEvent).bExecuteWhenPaused = true;		// bExecuteWhenPaused 允许游戏暂停时执行
	//绑定背包
	InputComponent->BindAction("PackageEvent", IE_Pressed, this, &ADemoPlayerController::PackageEvent);
	//聊天室
	InputComponent->BindAction("ChatRoomEvent", IE_Pressed, this, &ADemoPlayerController::ChatRoomEvent);

	//绑定缩放小地图事件
	InputComponent->BindAction("AddMapSize", IE_Pressed, this, &ADemoPlayerController::AddMapSizeStart);
	InputComponent->BindAction("AddMapSize", IE_Released, this, &ADemoPlayerController::AddMapSizeStop);
	InputComponent->BindAction("ReduceMapSize", IE_Pressed, this, &ADemoPlayerController::ReduceMapSizeStart);
	InputComponent->BindAction("ReduceMapSize", IE_Released, this, &ADemoPlayerController::ReduceMapSizeStop);
}


void ADemoPlayerController::EscEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		//设置游戏暂停
		SetPause(true);
		//设置输入模式为GameAndUI
		SwitchInputMode(false);
		//更新界面 运行委托
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Pause);
		//更新当前UI
		CurrentUIType = EGameUIType::Pause;
		//锁定输入
		LockedInput(true);
		break;
	case EGameUIType::Pause:
	case EGameUIType::Package:
	case EGameUIType::ChatRoom:
		//解除暂停
		SetPause(false);
		//设置游戏模式为游戏
		SwitchInputMode(true);
		//更新界面
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		//更新当前UI
		CurrentUIType = EGameUIType::Game;
		//解开输入
		LockedInput(false);
		break;
	}
}

void ADemoPlayerController::PackageEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Package);
		CurrentUIType = EGameUIType::Package;
		//锁定输入
		LockedInput(true);
		break;
	case EGameUIType::Package:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		//解开输入
		LockedInput(false);
		break;
	}
}

void ADemoPlayerController::ChatRoomEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::ChatRoom);
		CurrentUIType = EGameUIType::ChatRoom;
		//锁定输入
		LockedInput(true);
		break;
	case EGameUIType::ChatRoom:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		//解开输入
		LockedInput(false);
		break;
	}
}


void ADemoPlayerController::SwitchInputMode(bool IsGameOnly)
{
	if (IsGameOnly)
	{
		//隐藏鼠标
		bShowMouseCursor = false;
		//设置输入模式为OnlyGame
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);									// 响应鼠标点击
		SetInputMode(InputMode);
	}
	else
	{
		//显示鼠标
		bShowMouseCursor = true;
		//设置输入模式为GameAndUI
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);			// 锁定在游戏窗口
		InputMode.SetHideCursorDuringCapture(false);									// 是否隐藏
		SetInputMode(InputMode);														// 
	}
}

void ADemoPlayerController::LockedInput(bool IsLocked)
{
	SPCharacter->IsInputLocked = IsLocked;
}

void ADemoPlayerController::AddMapSizeStart()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//设置缩放状态为增加
	MiniMapSizeMode = EMiniMapSizeMode::Add;
}

void ADemoPlayerController::AddMapSizeStop()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ADemoPlayerController::ReduceMapSizeStart()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//设置缩放状态为减少
	MiniMapSizeMode = EMiniMapSizeMode::Reduce;
}

void ADemoPlayerController::ReduceMapSizeStop()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ADemoPlayerController::TickMiniMap()
{
	switch (MiniMapSizeMode)
	{
	case EMiniMapSizeMode::Add:
		UpdateMiniMapWidth.ExecuteIfBound(10);
		break;
	case EMiniMapSizeMode::Reduce:
		UpdateMiniMapWidth.ExecuteIfBound(-10);
		break;
	}
}


void ADemoPlayerController::PlayerDead()
{
	// 先转换到第三视角
	SPCharacter->ChangeView(EGameViewMode::Third);

	//告诉角色播放死亡动画,获得死亡时间
	float DeadDuration = SPCharacter->PlayDeadAnim();

	//锁住输入
	LockedInput(true);

	//添加时间委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ADemoPlayerController::DeadTimeOut);
	//通过时间委托延时跳转UI
	GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
}

void ADemoPlayerController::DeadTimeOut()
{
	//设置游戏暂停
	SetPause(true);
	//设置游戏模式为显示鼠标，输入模式为GameAndUI
	SwitchInputMode(false);
	//更新界面，显示失败
	ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Lose);
	//更新当前UI
	CurrentUIType = EGameUIType::Lose;
	//锁住输入
	LockedInput(true);
}

void ADemoPlayerController::ChangeHandObject()
{
	//生成手持物品
	SPCharacter->ChangeHandObject(ADemoHandObject::SpawnHandObject(SPState->GetCurrentHandObjectIndex()));
}

void ADemoPlayerController::ChangeView()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//如果不允许切换视角,直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;
	case EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;
	}
}

void ADemoPlayerController::LeftEventStart()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ADemoPlayerController::LeftEventStop()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ADemoPlayerController::RightEventStart()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ADemoPlayerController::RightEventStop()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ADemoPlayerController::ScrollUpEvent()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//如果不允许切换,直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	//如果鼠标有在按键不准跳转
	if (IsLeftButtonDown || IsRightButtonDown) return;

	//告诉状态类切换快捷栏容器
	SPState->ChooseShortcut(true);

	//更改Character的手持物品
	ChangeHandObject();
}

void ADemoPlayerController::ScrollDownEvent()
{
	//如果操作被锁住,直接返回
	if (SPCharacter->IsInputLocked) return;

	//如果不允许切换,直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	//如果鼠标有在按键不准跳转
	if (IsLeftButtonDown || IsRightButtonDown) return;

	//告诉状态类切换快捷栏容器
	SPState->ChooseShortcut(false);

	//更改Character的手持物品
	ChangeHandObject();
}

// 修改预动作
void ADemoPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//根据当前手持物品的类型来修改预动作
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//如果右键状态是拾取那就给拾取,拾取优先级高
		RightUpperType = RightType == EUpperBody::None ? EUpperBody::Eat : RightType;
		break;
	case EObjectType::Tool:
		LeftUpperType = EUpperBody::Hit;
		RightUpperType = RightType;
		break;
	case EObjectType::Weapon:
		LeftUpperType = EUpperBody::Fight;
		RightUpperType = RightType;
		break;
	}
}

// 射线检测结果
FHitResult ADemoPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	FCollisionQueryParams TraceParams(true);
	TraceParams.AddIgnoredActor(SPCharacter);
	// TraceParams.bTraceAsyncScene = true;		// 异步场景已经弃用
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);

	// 使用特定的通道跟踪光线，并返回第一个阻塞命中
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
	{
		//DrawRayLine(TraceStart, TraceEnd, 5.f);
	}

	return Hit;
}

// 射线绘制
void ADemoPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent* const LineBatcher = GetWorld()->PersistentLineBatcher;
	if (LineBatcher != nullptr) 
	{
		float LineDuration = (Duration > 0.f) ? Duration : LineBatcher->DefaultLifeTime;
		LineBatcher->DrawLine(StartPos, EndPos, FLinearColor::Red, 10, 0.f, LineDuration);	// 开始位置  结束位置 颜色 深度 
	}
}

// 进行射线检测
void ADemoPlayerController::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:		// 第一人称的起始位置
		StartPos = SPCharacter->FirstCamera->K2_GetComponentLocation();
		EndPos = StartPos + SPCharacter->FirstCamera->GetForwardVector() * 2000.f;
		break;
	case EGameViewMode::Third:		// 第三人称的起始位置
		StartPos = SPCharacter->ThirdCamera->K2_GetComponentLocation();
		StartPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 300.f;		// 开始位置 摄像机前方 300 的距离
		EndPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 2000.f;		// 结束位置
		break;
	}

	//是否检测到物品
	bool IsDetected = false;
	FHitResult Hit = RayGetHitResult(StartPos, EndPos);
	RayActor = Hit.GetActor();								// 获得检测到的 Actor

	if (Cast<ADemoPickupObject>(RayActor))					// 检测到的物品，是否是掉落物类
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoPickupObject>(RayActor)->GetInfoText();
	}
	if (Cast<ADemoResourceObject>(RayActor))				// 检测到的物品，是否是资源类
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoResourceObject>(RayActor)->GetInfoText();
	}
	if (Cast<ADemoEnemyCharacter>(RayActor))				// 检测到的物品，是否是怪物
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoEnemyCharacter>(RayActor)->GetInfoText();
	}

	//如果什么都没有检测到那就设置信息为无
	if (!IsDetected) 
	{
		SPState->RayInfoText = FText();
	}
}

void ADemoPlayerController::StateMachine()
{
	//普通模式
	ChangePreUpperType(EUpperBody::None);

	// 如果是 资源或可拾取物品 则准星不锁定（白色）
	if (!Cast<ADemoResourceObject>(RayActor) && !Cast<ADemoPickupObject>(RayActor) && !Cast<ADemoEnemyCharacter>(RayActor)) 
	{
		//准星显示未锁定
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}

	//如果检测到敌人 则锁定模式（）
	if (Cast<ADemoEnemyCharacter>(RayActor))
	{
		//准星锁定模式
		UpdatePointer.ExecuteIfBound(false, 0.f);
	}

	//如果检测到资源
	if (Cast<ADemoResourceObject>(RayActor)) 
	{
		//如果左键没有按下,在资源模式下右键没有特殊意义
		if (!IsLeftButtonDown) 
		{
			//准星锁定模式
			UpdatePointer.ExecuteIfBound(false, 0.f);
		}
		//如果左键已经按下
		if (IsLeftButtonDown && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) <= SPState->GetAffectRange())
		{
			// 根据资源类型，获取对其实际的伤害
			int Damage = SPState->GetDamageValue(Cast<ADemoResourceObject>(RayActor)->GetResourceType());

			//让资源受到伤害并且获取剩余血量百分比
			float Range = Cast<ADemoResourceObject>(RayActor)->TakeObjectDamage(Damage)->GetHPRange();

			//更新准星
			UpdatePointer.ExecuteIfBound(true, Range);
		}
	}

	//如果检测到可拾取物品,并且两者的距离小于300
	if (Cast<ADemoPickupObject>(RayActor) && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) <= 300.f)
	{
		//改变右键预状态为拾取
		ChangePreUpperType(EUpperBody::PickUp);

		//修改准星锁定模式
		UpdatePointer.ExecuteIfBound(false, 0);

		//如果右键按下
		if (IsRightButtonDown && SPCharacter->IsPackageFree(Cast<ADemoPickupObject>(RayActor)->ObjectIndex)) 
		{
			//把物品捡起来
			SPCharacter->AddPackageObject(Cast<ADemoPickupObject>(RayActor)->TakePickup());
		}
	}
}


