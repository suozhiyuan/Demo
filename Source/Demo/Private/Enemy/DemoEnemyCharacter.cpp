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

	//����AI������
	AIControllerClass = ADemoEnemyController::StaticClass();

	//������ײ�������ļ�
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	//GetCapsuleComponent()->bGenerateOverlapEvents = true;		// �������
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);		// �������

	//���ģ��
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'"));
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);		// ����Mesh
	GetMesh()->SetCollisionObjectType(ECC_Pawn);		// ��ײ��������
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// ������ײ����
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);				// ��Ӧ��ײͨ��
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//��Ӷ�����ͼ
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Animation.Enemy_Animation_C'"));	   // ע���ߵ� _C
	GetMesh()->AnimClass = StaticEnemyAnim.Class;

	//ʵ�������
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));
	SheildSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("SheildSocket"));

	//ʵ����Ѫ��
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->AttachTo(RootComponent);

	//ʵ�������˸�֪���
	EnemySense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("EnemySense"));

	//��������������Դ
	AnimDead_I = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_I.Enemy_Dead_I'")));
	AnimDead_II = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_II.Enemy_Dead_II'")));

	////������һ֡�������Լ�,�÷��ڹ��캯�����г�ʼ��,������GameMode�ļ��غ�����ͻ
	//IsDestroyNextTick = false;
}

// Called when the game starts or when spawned
void ADemoEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//��ȡ��������
	SEAnim = Cast<UDemoEnemyAnim>(GetMesh()->GetAnimInstance());
	SEController = Cast<ADemoEnemyController>(GetController());

	//�󶨲��
	WeaponSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
	SheildSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LHSocket"));

	//����������Ʒ
	WeaponSocket->SetChildActorClass(ADemoEnemyTool::SpawnEnemyWeapon());
	SheildSocket->SetChildActorClass(ADemoEnemyTool::SpawnEnemySheild());

	//����Ѫ��widget
	SAssignNew(HPBarWidget, SDemoEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));
	//���ó�ʼѪ��
	HP = 200.f;
	HPBarWidget->ChangeHP(HP / 200.f);

	//���˸�֪��������
	EnemySense->HearingThreshold = 0.f;					// �����ڵ�ʱ������
	EnemySense->LOSHearingThreshold = 0.f;				// 
	EnemySense->SightRadius = 1000.f;					// �����Ұ����
	EnemySense->SetPeripheralVisionAngle(55.f);			// �����Ұ�Ƕ�
	EnemySense->bHearNoises = false;					// �Ƿ������������

	//�󶨿�����ҵķ���
	FScriptDelegate OnSeePlayerDele;
	OnSeePlayerDele.BindUFunction(this, "OnSeePlayer");
	EnemySense->OnSeePawn.Add(OnSeePlayerDele);

	//������ԴID��3
	ResourceIndex = 3;
}

//�����ʵ���
void ADemoEnemyCharacter::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);

	//��������
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It)
	{
		//�����
		FRandomStream Stream;
		//�����µ��������
		Stream.GenerateNewSeed();
		//��������������ĵ�2�͵�3��ֵ
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld())
		{
			for (int i = 0; i < Num; ++i)
			{
				//���ɵ�����Դ
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

	////���׼������Ϊtrue,��������
	//if (IsDestroyNextTick) DestroyEvent();
}

// Called to bind functionality to input
void ADemoEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADemoEnemyCharacter::UpdateHPBarRotation(FVector SPLoaction)
{
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);						// �ҵ�λ�� ������˵ķ���
	FVector TargetPos(SPLoaction.X, SPLoaction.Y, 0.f);									// Ŀ��λ��
	HPBar->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}

void ADemoEnemyCharacter::SetMaxSpeed(float Speed)
{
	//��������˶��ٶ�
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float ADemoEnemyCharacter::GetIdleWaitTime()
{
	//���������ͼ������ֱ�ӷ���3��
	if (!SEAnim) return 3.f;

	//���������
	FRandomStream Stream;
	Stream.GenerateNewSeed();		// ����һ���µ��������
	int IdleTpye = Stream.RandRange(0, 2);
	float AnimLength = SEAnim->SetIdelType(IdleTpye);		// ͨ�������ȷ��һ������

	//��������
	Stream.GenerateNewSeed();

	//������������
	int AnimCount = Stream.RandRange(1, 3);

	//����ȫ���Ķ���ʱ��
	return AnimLength * AnimCount;
}

float ADemoEnemyCharacter::PlayAttackAction(EEnemyAttackType AttackType)
{
	//���������ͼ������ֱ�ӷ���0��
	if (!SEAnim) return 0.f;

	//���ع���ʱ��
	return SEAnim->PlayAttackAction(AttackType);
}

// ���ܹ�ji
void ADemoEnemyCharacter::AcceptDamage(int DamageVal)
{
	//��������˷���,ֱ�ӷ���
	if (SEAnim && SEAnim->IsDefence) return;

	//����Ѫֵ����
	HP = FMath::Clamp<float>(HP - DamageVal, 0.f, 500.f);		
	HPBarWidget->ChangeHP(HP / 200.f);

	//���ѪֵС��0
	if (HP == 0.f && !DeadHandle.IsValid())			// DeadHandle.IsValid() �����������������ʱ����������ʼ������ΪTrue
	{
		//���߿�����������ֹͣ��Ϊ��
		SEController->EnemyDead();

		//ֹͣ���ж���
		SEAnim->StopAllAction();

		// ������ʱ��ʱ��
		float DeadDuration = 0.f;

		// �����
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		int SelectIndex = Stream.RandRange(0, 1);

		if (SelectIndex == 0)
		{
			GetMesh()->PlayAnimation(AnimDead_I, false);			// �ڶ����������Ƿ�ѭ������ѭ���Ļ���һֱͣ�������һ֡
			DeadDuration = AnimDead_I->GetMaxCurrentTime() * 2;			// ��ȡִ��ʱ��,����ͣ��ʱ��
		}
		else
		{
			GetMesh()->PlayAnimation(AnimDead_II, false);
			DeadDuration = AnimDead_II->GetMaxCurrentTime() * 2;
		}

		//���ɵ�����
		CreateFlobObject();

		//����¼�ί��
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ADemoEnemyCharacter::DestroyEvent);		// ��
		GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);		// ��ʱ��
	}
	else
	{
		//���߿������յ��˺�
		if (SEController) SEController->UpdateDamageRatio(HP / 200.f);
	}
}

float ADemoEnemyCharacter::PlayHurtAction()
{
	//���������ͼ������ֱ�ӷ���0��
	if (!SEAnim) return 0.f;
	//���ع���ʱ��
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
	//ע��ʱ�亯��
	if (DeadHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(DeadHandle);

	//�����Լ�
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
//	//����ֳ���Ʒ����,�޸ļ��
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
//	//�޸�Ѫ����ʾ
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
		// ���߿������ҿ��������
		if (SEController) SEController->OnSeePlayer();
	}
}