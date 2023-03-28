// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource/DemoResourceObject.h"
#include "Components/StaticMeshComponent.h"
#include "Data/DemoDataHandle.h"
#include "Engine/GameEngine.h"


// Sets default values
ADemoResourceObject::ADemoResourceObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//实例化模型组件
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));			// 设置碰撞

	//开启交互检测
	BaseMesh->SetGenerateOverlapEvents(true);

	//设置在下一帧不销毁
	//IsDestroyNextTick = false;
}

 // Called when the game starts or when spawned
void ADemoResourceObject::BeginPlay()
{
	Super::BeginPlay();

	//初始化游戏数据，原本在GameMode的BeginPlay中调用，但资源模型在游戏中加载时 GameMode 的 BeginPlay 还没有调用，就暂时先移到这里了
	DemoDataHandle::Get()->InitializeGameData();

	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	BaseHP = ResourceAttr->HP;
	HP = ResourceAttr->HP;
}

//void ADemoResourceObject::CreateFlobObject()
//{
//	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
//	//遍历生成掉落物
//	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It) {
//		//随机生成的数量
//		FRandomStream Stream;
//		Stream.GenerateNewSeed();
//		//生成数量
//		int Num = Stream.RandRange((*It)[1], (*It)[2]);
//
//		if (GetWorld()) {
//			for (int i = 0; i < Num; ++i) {
//				//生成掉落物
//				ADemoFlobObject* FlobObject = GetWorld()->SpawnActor<ADemoFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 20.f), FRotator::ZeroRotator);
//				FlobObject->CreateFlobObject((*It)[0]);
//			}
//		}
//	}
//}

// Called every frame
void ADemoResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//如果检测到下一帧要销毁
	//if (IsDestroyNextTick) GetWorld()->DestroyActor(this);

}

// 获取物品信息
FText ADemoResourceObject::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (DemoDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;
		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;
		break;
	}
	return ResourceAttr->ZH;
}


// 获取资源类型
EResourceType::Type ADemoResourceObject::GetResourceType()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	return ResourceAttr->ResourceType;
}

// 获取血量百分比
float ADemoResourceObject::GetHPRange()
{
	return FMath::Clamp<float>((float)HP / (float)BaseHP, 0.f, 1.f);
}

// 将伤害带入，血量计算
ADemoResourceObject* ADemoResourceObject::TakeObjectDamage(int Damage)
{
	HP = FMath::Clamp<int>(HP - Damage, 0, BaseHP);

	if (HP <= 0) 
	{
		//检测失效
		BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

		////创建掉落物
		//CreateFlobObject();

		//销毁物体
		GetWorld()->DestroyActor(this);
	}
	return this;
}