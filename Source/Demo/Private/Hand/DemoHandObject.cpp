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

	//实例化根组件
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;													// 设置为根组件

	//创建静态模型组件
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);									// 添加到根组件
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));					// 设置碰撞

	//实现碰撞组件
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(RootComponent);
	AffectCollision->SetCollisionProfileName(FName("ToolProfile"));

	//初始时关闭 Overlay 检测，只有在特定时间打开
	AffectCollision->SetGenerateOverlapEvents(false);

	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;		// 脚本委托
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);

	////默认拳头音效
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
	//	//获取物品属性
	//	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	//	//获取对动物的伤害值
	//	Cast<ADemoEnemyCharacter>(OtherActor)->AcceptDamage(ObjectAttr->AnimalAttack);
	//}
	////如果音效存在,播放音效,默认音效为拳打
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