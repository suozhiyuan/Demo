// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/DemoPickupObject.h"

#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"

// Sets default values
ADemoPickupObject::ADemoPickupObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootScene;
	
	//在这里实现模型组件但是不进行模型绑定
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	//设置模型碰撞为PickupProfile
	BaseMesh->SetCollisionProfileName(FName("PickupProfile"));

	////设置下一帧不销毁
	//IsDestroyNextTick = false;
}

// Called when the game starts or when spawned
void ADemoPickupObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADemoPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////如果下一帧销毁,自行销毁
	//if (IsDestroyNextTick) GetWorld()->DestroyActor(this);

}

FText ADemoPickupObject::GetInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	switch (DemoDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
	}
	return ObjectAttr->ZH;
}

int ADemoPickupObject::TakePickup()
{
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);		// 因为是在下一帧销毁，所以需要先忽略下
	if (GetWorld()) GetWorld()->DestroyActor(this);
	return ObjectIndex;
}

