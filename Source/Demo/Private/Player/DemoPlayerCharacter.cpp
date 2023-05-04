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

	//��ʼ����������ײ�������ΪPlayerProfile,����Ĺ���ģ�͵���ײ�Ͷ���������Ϊ����ײ
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));

	//��ӵ�һ�˳ƹ���ģ��
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());							// �������ĸ�����ϣ���������� RootComponent
	MeshFirst->bOnlyOwnerSee = true;																// �����ֵΪTrue��������������ͼ�������Ǹ������ֱ�ӻ���������ʱ�ſɼ���
	MeshFirst->bCastDynamicShadow = false;															// �Ƿ�Ͷ��Ӱ��
	MeshFirst->bReceivesDecals = false;																// �Ƿ��������
	// ����Ƶ��
	MeshFirst->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;		// Ӱ�����ܵĲ���������ˢ�µ�Ƶ��
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;													// ˢ��˳�򣬲���Ϊˢ����
	// ������ײ����
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	// ����λ��
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	// ��ȡ��һ�˳ƵĶ�����ͼ  ������ͼ������ FClassFinder��·���������Ҫ�� _C
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;

	//��Ĭ��Mesh��ӹ���ģ��  ���� UObject ������ FObjectFinder
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);												// �� ����ģ�� ���� Mesh
	GetMesh()->bOnlyOwnerSee = true;																// �����ֵΪTrue��������������ͼ�������Ǹ������ֱ�ӻ���������ʱ�ſɼ���
	GetMesh()->bReceivesDecals = false;																// �Ƿ��������
	GetMesh()->SetCollisionObjectType(ECC_Pawn);												// �ڹǼ�������������ײ��������
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);							// ������ײ����
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);										// ��Ӧ��ײͨ��
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));							// λ���ƶ�����ԣ�
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));		// �Ƕ���ת����ԣ�

	//��ȡ�����˳ƵĶ�����ͼ
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;

	//�����ҡ�� ������ͨ������Component������ CreateDefaultSubobject
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);										// ���ӵ��ĸ����
	CameraBoom->TargetArmLength = 300.f;											// ���þ���
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);					// ����ƫ��
	CameraBoom->bUsePawnControlRotation = true;										// ��Controller����ת

	//��ʼ�������˳������
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);		// ����ΪɶҪ�� USpringArmComponent::SocketName  ������
	ThirdCamera->bUsePawnControlRotation = false;									// ���� ThirdCamera ���������������ת

	//��ʼ����һ�˳������
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FirstCamera->bUsePawnControlRotation = true;									// ���ø���Controller����ת
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));		// ����ƫ�� 

	//Ĭ�ϵ����˳�
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);

	//����ʾ��һ�˳�ģ��
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

	//ʵ����������Ʒ
	HandObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("HandObject"));

	//��������������Դ
	AnimDead = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/Player_Death.Player_Death'")));

	//��ʼ������
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//���ó�ʼ�ٶ�Ϊ150.f
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	//��ʼΪ�����˳�
	GameView = EGameViewMode::Third;

	//�ϰ�������ʼΪ�޶���
	UpperType = EUpperBody::None;

	//һ��ʼ�����л��ӽ�
	IsAllowSwitch = true;

	//һ��ʼ���벻��ס����
	IsInputLocked = false;

	//��ʼ��û�й���
	IsAttack = false;
}

// Called when the game starts or when spawned
void ADemoPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//���������ָ��Ϊ��,�������
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//���ֳ���Ʒ����󶨵������˳�ģ�����ֲ����
	HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));

	//���Actor��HandObject����Ϸһ��ʼĬ�Ͼ��ǿ�����
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
		MeshFirst->SetOwnerNoSee(false);					// ��һ�˳� Mesh ����ʾ
		GetMesh()->SetOwnerNoSee(true);						// �����˳� Mesh 
		// �޸� handobject �󶨵�λ�õ���һ�˳� Mesh
		HandObject->AttachToComponent(MeshFirst, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		// �޸� handobject �󶨵�λ�õ������˳� Mesh
		HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	}
}

void ADemoPlayerCharacter::ChangeHandObject(TSubclassOf<AActor> HandObjectClass)
{
	//������Ʒ�� HandObject
	HandObject->SetChildActorClass(HandObjectClass);
}

void ADemoPlayerCharacter::ChangeHandObjectDetect(bool IsOpen)
{
	//��ȡ������Ʒ
	ADemoHandObject* HandObjectClass = Cast<ADemoHandObject>(HandObject->GetChildActor());
	if (HandObjectClass) HandObjectClass->ChangeOverlayDetect(IsOpen);

	//�޸Ĺ���״̬
	IsAttack = IsOpen;
}

//�Ƿ���Ⱦ������Ʒ,��Anim���е���
void ADemoPlayerCharacter::RenderHandObject(bool IsRender)
{
	//���������Ʒľ��
	if (!HandObject->GetChildActor()) return;

	//�������Ʒ
	HandObject->GetChildActor()->SetActorHiddenInGame(!IsRender);		// SetActorHiddenInGame   ����
}

void ADemoPlayerCharacter::PlayerThrowObject(int ObjectID, int Num)
{
	if (GetWorld()) 
	{
		for (int i = 0; i < Num; ++i) 
		{
			//���ɵ�����Դ
			ADemoFlobObject* FlobObject = GetWorld()->SpawnActor<ADemoFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 50.f), FRotator::ZeroRotator);

			//�Զ�����ʽ���ɵ�����
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
	//�������û�״̬Ϊ��,ֱ�ӷ���
	if (!SPController->SPState) return;
	//���߱����ĸ���������˶���,����ɹ��Ե�����
	if (DemoPackageManager::Get()->EatUpEvent(SPController->SPState->CurrentShortcutIndex))
	{
		//�������״̬����������ֵ
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
	//�����������ס,ֱ�ӷ���
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
	//�����������ס,ֱ�ӷ���
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
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADemoPlayerCharacter::Turn(float Value)
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	AddControllerYawInput(Value);
}

void ADemoPlayerCharacter::TurnAtRate(float Value)
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADemoPlayerCharacter::OnStartJump()
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	bPressedJump = true;
}

void ADemoPlayerCharacter::OnStopJump()
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	bPressedJump = false;
	StopJumping();
}

void ADemoPlayerCharacter::OnStartRun()
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	GetCharacterMovement()->MaxWalkSpeed = 375.f;
}

void ADemoPlayerCharacter::OnStopRun()
{
	//�����������ס,ֱ�ӷ���
	if (IsInputLocked) return;

	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}