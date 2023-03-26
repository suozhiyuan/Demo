// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/DemoHandObject.h"

#include "Components/BoxComponent.h"
#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADemoHandObject::ADemoHandObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ʵ���������
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;													// ����Ϊ�����

	//������̬ģ�����
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);									// ��ӵ������
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));					// ������ײ

	//ʵ����ײ���
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(RootComponent);
	AffectCollision->SetCollisionProfileName(FName("ToolProfile"));

	//��ʼʱ�ر� Overlay ��⣬ֻ�����ض�ʱ���
	AffectCollision->SetGenerateOverlapEvents(false);

	//�󶨼�ⷽ������ײ��
	FScriptDelegate OverlayBegin;		// �ű�ί��
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);

	////Ĭ��ȭͷ��Ч
	//static ConstructorHelpers::FObjectFinder<USoundWave> StaticSound(TEXT("SoundWave'/Game/Res/Sound/GameSound/Punch.Punch'"));
	//OverlaySound = StaticSound.Object;
}

 // Called when the game starts or when spawned
void ADemoHandObject::BeginPlay()
{
	Super::BeginPlay();

}

void ADemoHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<ADemoEnemyCharacter>(OtherActor))
	//{
	//	//��ȡ��Ʒ����
	//	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	//	//��ȡ�Զ�����˺�ֵ
	//	Cast<ADemoEnemyCharacter>(OtherActor)->AcceptDamage(ObjectAttr->AnimalAttack);
	//}
	////�����Ч����,������Ч,Ĭ����ЧΪȭ��
	//if (OverlaySound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlaySound, OtherActor->GetActorLocation());
}

void ADemoHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ADemoHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TSubclassOf<AActor> ADemoHandObject::SpawnHandObject(int ObjectID)
//{
//	switch (ObjectID)
//	{
//	case 0:
//		return ADemoHandNone::StaticClass();
//	case 1:
//		return ADemoHandWood::StaticClass();
//	case 2:
//		return ADemoHandStone::StaticClass();
//	case 3:
//		return ADemoHandApple::StaticClass();
//	case 4:
//		return ADemoHandMeat::StaticClass();
//	case 5:
//		return ADemoHandAxe::StaticClass();
//	case 6:
//		return ADemoHandHammer::StaticClass();
//	case 7:
//		return ADemoHandSword::StaticClass();
//	}
//
//	return ADemoHandNone::StaticClass();
//}
//
//void ADemoHandObject::ChangeOverlayDetect(bool IsOpen)
//{
//	AffectCollision->bGenerateOverlapEvents = IsOpen;
//}