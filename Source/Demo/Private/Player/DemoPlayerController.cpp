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
	//����ÿ֡����
	PrimaryActorTick.bCanEverTick = true;
}

void ADemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//��ȡ��ɫ��״̬
	if (!SPCharacter) SPCharacter = Cast<ADemoPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ADemoPlayerState>(PlayerState);

	//������겻��ʾ
	bShowMouseCursor = false;

	//��������ģʽ�� GameOnly �� GameUI ���Ի���ת���������ת���� UIOnly �㲻��ת������������ģʽ
	FInputModeGameOnly InputMode;					// ��������ֻ�����������/��ҿ�������Ӧ�û����������ģʽ�����ݽṹ��
	InputMode.SetConsumeCaptureMouseDown(true);		// �Ƿ񲶻������
	SetInputMode(InputMode);						// ��������ģʽ

	//����Ԥ����
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	//��ʼ���Ƿ�ס����
	IsLeftButtonDown = false;
	IsRightButtonDown = false;

	//����Ĭ��UI״̬Ϊ��Ϸ����
	CurrentUIType = EGameUIType::Game;

	//��������״̬Ϊ��
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ADemoPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ��ʱ����
	ChangePreUpperType(EUpperBody::None);

	// Բ�ν����� ���Դ���
	//static float TestPointer = 1.f;
	//TestPointer = FMath::FInterpTo(TestPointer, 0, DeltaSeconds, 1.f);
	//UpdatePointer.ExecuteIfBound(true, FMath::Clamp(TestPointer, 0.f, 1.f));

	//�������߼��
	RunRayCast();

	// ������״̬
	StateMachine();

	//����С��ͼ����
	TickMiniMap();
}

void ADemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//���ӽ��л�
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ADemoPlayerController::ChangeView);
	//����갴���¼�
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ADemoPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ADemoPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ADemoPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ADemoPlayerController::RightEventStop);

	//����껬���¼�
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ADemoPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ADemoPlayerController::ScrollDownEvent);

	//��ESC���¼��������õ���ͣ��Ϸ��ʱ����Ȼ��������
	InputComponent->BindAction("EscEvent", IE_Pressed, this, &ADemoPlayerController::EscEvent).bExecuteWhenPaused = true;		// bExecuteWhenPaused ������Ϸ��ͣʱִ��
	//�󶨱���
	InputComponent->BindAction("PackageEvent", IE_Pressed, this, &ADemoPlayerController::PackageEvent);
	//������
	InputComponent->BindAction("ChatRoomEvent", IE_Pressed, this, &ADemoPlayerController::ChatRoomEvent);

	//������С��ͼ�¼�
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
		//������Ϸ��ͣ
		SetPause(true);
		//��������ģʽΪGameAndUI
		SwitchInputMode(false);
		//���½��� ����ί��
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Pause);
		//���µ�ǰUI
		CurrentUIType = EGameUIType::Pause;
		//��������
		LockedInput(true);
		break;
	case EGameUIType::Pause:
	case EGameUIType::Package:
	case EGameUIType::ChatRoom:
		//�����ͣ
		SetPause(false);
		//������ϷģʽΪ��Ϸ
		SwitchInputMode(true);
		//���½���
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		//���µ�ǰUI
		CurrentUIType = EGameUIType::Game;
		//�⿪����
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
		//��������
		LockedInput(true);
		break;
	case EGameUIType::Package:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		//�⿪����
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
		//��������
		LockedInput(true);
		break;
	case EGameUIType::ChatRoom:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		//�⿪����
		LockedInput(false);
		break;
	}
}


void ADemoPlayerController::SwitchInputMode(bool IsGameOnly)
{
	if (IsGameOnly)
	{
		//�������
		bShowMouseCursor = false;
		//��������ģʽΪOnlyGame
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);									// ��Ӧ�����
		SetInputMode(InputMode);
	}
	else
	{
		//��ʾ���
		bShowMouseCursor = true;
		//��������ģʽΪGameAndUI
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);			// ��������Ϸ����
		InputMode.SetHideCursorDuringCapture(false);									// �Ƿ�����
		SetInputMode(InputMode);														// 
	}
}

void ADemoPlayerController::LockedInput(bool IsLocked)
{
	SPCharacter->IsInputLocked = IsLocked;
}

void ADemoPlayerController::AddMapSizeStart()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//��������״̬Ϊ����
	MiniMapSizeMode = EMiniMapSizeMode::Add;
}

void ADemoPlayerController::AddMapSizeStop()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//��������״̬Ϊ��
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ADemoPlayerController::ReduceMapSizeStart()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//��������״̬Ϊ����
	MiniMapSizeMode = EMiniMapSizeMode::Reduce;
}

void ADemoPlayerController::ReduceMapSizeStop()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//��������״̬Ϊ��
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
	// ��ת���������ӽ�
	SPCharacter->ChangeView(EGameViewMode::Third);

	//���߽�ɫ������������,�������ʱ��
	float DeadDuration = SPCharacter->PlayDeadAnim();

	//��ס����
	LockedInput(true);

	//���ʱ��ί��
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ADemoPlayerController::DeadTimeOut);
	//ͨ��ʱ��ί����ʱ��תUI
	GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
}

void ADemoPlayerController::DeadTimeOut()
{
	//������Ϸ��ͣ
	SetPause(true);
	//������ϷģʽΪ��ʾ��꣬����ģʽΪGameAndUI
	SwitchInputMode(false);
	//���½��棬��ʾʧ��
	ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Lose);
	//���µ�ǰUI
	CurrentUIType = EGameUIType::Lose;
	//��ס����
	LockedInput(true);
}

void ADemoPlayerController::ChangeHandObject()
{
	//�����ֳ���Ʒ
	SPCharacter->ChangeHandObject(ADemoHandObject::SpawnHandObject(SPState->GetCurrentHandObjectIndex()));
}

void ADemoPlayerController::ChangeView()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//����������л��ӽ�,ֱ�ӷ���
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
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ADemoPlayerController::LeftEventStop()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ADemoPlayerController::RightEventStart()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ADemoPlayerController::RightEventStop()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ADemoPlayerController::ScrollUpEvent()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//����������л�,ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	//���������ڰ�����׼��ת
	if (IsLeftButtonDown || IsRightButtonDown) return;

	//����״̬���л����������
	SPState->ChooseShortcut(true);

	//����Character���ֳ���Ʒ
	ChangeHandObject();
}

void ADemoPlayerController::ScrollDownEvent()
{
	//�����������ס,ֱ�ӷ���
	if (SPCharacter->IsInputLocked) return;

	//����������л�,ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	//���������ڰ�����׼��ת
	if (IsLeftButtonDown || IsRightButtonDown) return;

	//����״̬���л����������
	SPState->ChooseShortcut(false);

	//����Character���ֳ���Ʒ
	ChangeHandObject();
}

// �޸�Ԥ����
void ADemoPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//���ݵ�ǰ�ֳ���Ʒ���������޸�Ԥ����
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//����Ҽ�״̬��ʰȡ�Ǿ͸�ʰȡ,ʰȡ���ȼ���
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

// ���߼����
FHitResult ADemoPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	FCollisionQueryParams TraceParams(true);
	TraceParams.AddIgnoredActor(SPCharacter);
	// TraceParams.bTraceAsyncScene = true;		// �첽�����Ѿ�����
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);

	// ʹ���ض���ͨ�����ٹ��ߣ������ص�һ����������
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
	{
		//DrawRayLine(TraceStart, TraceEnd, 5.f);
	}

	return Hit;
}

// ���߻���
void ADemoPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent* const LineBatcher = GetWorld()->PersistentLineBatcher;
	if (LineBatcher != nullptr) 
	{
		float LineDuration = (Duration > 0.f) ? Duration : LineBatcher->DefaultLifeTime;
		LineBatcher->DrawLine(StartPos, EndPos, FLinearColor::Red, 10, 0.f, LineDuration);	// ��ʼλ��  ����λ�� ��ɫ ��� 
	}
}

// �������߼��
void ADemoPlayerController::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:		// ��һ�˳Ƶ���ʼλ��
		StartPos = SPCharacter->FirstCamera->K2_GetComponentLocation();
		EndPos = StartPos + SPCharacter->FirstCamera->GetForwardVector() * 2000.f;
		break;
	case EGameViewMode::Third:		// �����˳Ƶ���ʼλ��
		StartPos = SPCharacter->ThirdCamera->K2_GetComponentLocation();
		StartPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 300.f;		// ��ʼλ�� �����ǰ�� 300 �ľ���
		EndPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector() * 2000.f;		// ����λ��
		break;
	}

	//�Ƿ��⵽��Ʒ
	bool IsDetected = false;
	FHitResult Hit = RayGetHitResult(StartPos, EndPos);
	RayActor = Hit.GetActor();								// ��ü�⵽�� Actor

	if (Cast<ADemoPickupObject>(RayActor))					// ��⵽����Ʒ���Ƿ��ǵ�������
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoPickupObject>(RayActor)->GetInfoText();
	}
	if (Cast<ADemoResourceObject>(RayActor))				// ��⵽����Ʒ���Ƿ�����Դ��
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoResourceObject>(RayActor)->GetInfoText();
	}
	if (Cast<ADemoEnemyCharacter>(RayActor))				// ��⵽����Ʒ���Ƿ��ǹ���
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ADemoEnemyCharacter>(RayActor)->GetInfoText();
	}

	//���ʲô��û�м�⵽�Ǿ�������ϢΪ��
	if (!IsDetected) 
	{
		SPState->RayInfoText = FText();
	}
}

void ADemoPlayerController::StateMachine()
{
	//��ͨģʽ
	ChangePreUpperType(EUpperBody::None);

	// ����� ��Դ���ʰȡ��Ʒ ��׼�ǲ���������ɫ��
	if (!Cast<ADemoResourceObject>(RayActor) && !Cast<ADemoPickupObject>(RayActor) && !Cast<ADemoEnemyCharacter>(RayActor)) 
	{
		//׼����ʾδ����
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}

	//�����⵽���� ������ģʽ����
	if (Cast<ADemoEnemyCharacter>(RayActor))
	{
		//׼������ģʽ
		UpdatePointer.ExecuteIfBound(false, 0.f);
	}

	//�����⵽��Դ
	if (Cast<ADemoResourceObject>(RayActor)) 
	{
		//������û�а���,����Դģʽ���Ҽ�û����������
		if (!IsLeftButtonDown) 
		{
			//׼������ģʽ
			UpdatePointer.ExecuteIfBound(false, 0.f);
		}
		//�������Ѿ�����
		if (IsLeftButtonDown && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) <= SPState->GetAffectRange())
		{
			// ������Դ���ͣ���ȡ����ʵ�ʵ��˺�
			int Damage = SPState->GetDamageValue(Cast<ADemoResourceObject>(RayActor)->GetResourceType());

			//����Դ�ܵ��˺����һ�ȡʣ��Ѫ���ٷֱ�
			float Range = Cast<ADemoResourceObject>(RayActor)->TakeObjectDamage(Damage)->GetHPRange();

			//����׼��
			UpdatePointer.ExecuteIfBound(true, Range);
		}
	}

	//�����⵽��ʰȡ��Ʒ,�������ߵľ���С��300
	if (Cast<ADemoPickupObject>(RayActor) && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) <= 300.f)
	{
		//�ı��Ҽ�Ԥ״̬Ϊʰȡ
		ChangePreUpperType(EUpperBody::PickUp);

		//�޸�׼������ģʽ
		UpdatePointer.ExecuteIfBound(false, 0);

		//����Ҽ�����
		if (IsRightButtonDown && SPCharacter->IsPackageFree(Cast<ADemoPickupObject>(RayActor)->ObjectIndex)) 
		{
			//����Ʒ������
			SPCharacter->AddPackageObject(Cast<ADemoPickupObject>(RayActor)->TakePickup());
		}
	}
}


