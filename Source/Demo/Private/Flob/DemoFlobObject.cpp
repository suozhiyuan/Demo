// Fill out your copyright notice in the Description page of Project Settings.


#include "Flob/DemoFlobObject.h"

#include "Components/BoxComponent.h"
#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"

// Sets default values
ADemoFlobObject::ADemoFlobObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = (USceneComponent*)BoxCollision;

	//������ײ����
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));

	//��������ģ�⣬�����������е��������������ײ���
	BoxCollision->SetSimulatePhysics(true);

	//������ת
	BoxCollision->SetConstraintMode(EDOFMode::Default);				// EDOFMode::Default ����Ŀ�����м̳����ɶȡ�
	BoxCollision->GetBodyInstance()->bLockXRotation = true;
	BoxCollision->GetBodyInstance()->bLockYRotation = true;
	BoxCollision->GetBodyInstance()->bLockZRotation = true;

	//���ô�С
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);			// �������ԭʼ���������ResponseToChannels����
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);		// ���ƴ����������������͵���ײ

	//���ñ任
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	// ����ʵ��
	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));

	//��̬��������
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);
}

// Called when the game starts or when spawned
void ADemoFlobObject::BeginPlay()
{
	Super::BeginPlay();

	////��������Ƿ����
	//if (!GetWorld()) return;

	////ע�����¼�
	//FTimerDelegate DetectPlayerDele;
	//DetectPlayerDele.BindUObject(this, &ADemoFlobObject::DetectPlayer);
	////ÿ������һ��,ѭ������,�ӳ�3������
	//GetWorld()->GetTimerManager().SetTimer(DetectTimer, DetectPlayerDele, 1.f, true, 3.f);

	////ע�������¼�
	//FTimerDelegate DestroyDele;
	//DestroyDele.BindUObject(this, &ADemoFlobObject::DestroyEvent);
	//GetWorld()->GetTimerManager().SetTimer(DestroyTimer, DestroyDele, 30.f, false);

	////��ʼ���ָ��Ϊ��
	//SPCharacter = NULL;
}

// Called every frame
void ADemoFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////һֱ��ת
	//BaseMesh->AddLocalRotation(FRotator(DeltaTime * 60.f, 0.f, 0.f));

	////�����⵽���
	//if (SPCharacter) {
	//	//�������
	//	SetActorLocation(FMath::VInterpTo(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f), DeltaTime, 5.f));
	//	//�������ӽ�0
	//	if (FVector::Distance(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f)) < 10.f)
	//	{
	//		//�ж���ұ����Ƿ��пռ�
	//		if (SPCharacter->IsPackageFree(ObjectIndex)) {
	//			//��Ӷ�Ӧ����Ʒ������
	//			SPCharacter->AddPackageObject(ObjectIndex);
	//			//�����Լ�
	//			DestroyEvent();
	//		}
	//		else {
	//			//�����ұ�����Ϊ��,���ò���
	//			SPCharacter = NULL;
	//			//���Ѽ��
	//			GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
	//			//���������߳�
	//			GetWorld()->GetTimerManager().UnPauseTimer(DestroyTimer);
	//			//��������ģ��
	//			BoxCollision->SetSimulatePhysics(true);
	//		}
	//	}
	//}
}

void ADemoFlobObject::CreateFlobObject(int ObjectID)
{
	//ָ��ID
	ObjectIndex = ObjectID;

	//��Ⱦ��ͼ
	RenderTexture();

	//������������
	FRandomStream Stream;
	Stream.GenerateNewSeed();											// �����������
	int DirYaw = Stream.RandRange(-180, 180);					// ��һ����Χ�����һ���Ƕ�
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);			// �����ֵ���뵽 Yaw

	//�����
	BoxCollision->AddForce((FVector(0.f, 0.f, 4.f) + ForceRot.Vector()) * 100000.f);
}


//void ADemoFlobObject::ThrowFlobObject(int ObjectID, float DirYaw)
//{
//	//ָ��ID
//	ObjectIndex = ObjectID;
//
//	//��Ⱦ��ͼ
//	RenderTexture();
//
//	//������������
//	FRandomStream Stream;
//
//	//�����µ��������
//	Stream.GenerateNewSeed();
//
//	//���ƫ�Ʒ���
//	DirYaw += Stream.RandRange(-30, 30);
//
//	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);
//
//	//�����
//	BoxCollision->AddForce((FVector(0.f, 0.f, 2.f) + ForceRot.Vector()) * 120000.f);
//}

void ADemoFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);							// ��ͼ·��
	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);					// ��ͼ������̬����
	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}

//void ADemoFlobObject::DetectPlayer()
//{
//	//��������Ƿ����
//	if (!GetWorld()) return;
//
//	//��������
//	TArray<FOverlapResult> Overlaps;
//	FCollisionObjectQueryParams ObjectParams;
//	FCollisionQueryParams Params;
//	Params.AddIgnoredActor(this);
//	Params.bTraceAsyncScene = true;
//
//	//���ж�̬���,��ⷶΧ��200,���ɹ��Ļ�����true
//	if (GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(200.f), Params))
//	{
//		for (TArray<FOverlapResult>::TIterator It(Overlaps); It; ++It) {
//			//�����⵽�����
//			if (Cast<ADemoPlayerCharacter>(It->GetActor())) {
//				//��ֵ
//				SPCharacter = Cast<ADemoPlayerCharacter>(It->GetActor());
//				//��������пռ�,��������Ӻ���
//				if (SPCharacter->IsPackageFree(ObjectIndex))
//				{
//					//ֹͣ���
//					GetWorld()->GetTimerManager().PauseTimer(DetectTimer);
//					//ֹͣ���ٶ�ʱ��
//					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);
//					//�ر�����ģ��
//					BoxCollision->SetSimulatePhysics(false);
//				}
//				return;
//			}
//		}
//	}
//}
//
//void ADemoFlobObject::DestroyEvent()
//{
//	if (!GetWorld()) return;
//	//ע����ʱ��
//	GetWorld()->GetTimerManager().ClearTimer(DetectTimer);
//	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
//	//�����Լ�
//	GetWorld()->DestroyActor(this);
//}
