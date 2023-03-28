// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/DemoPickupObject.h"

#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"

// Sets default values
ADemoPickupObject::ADemoPickupObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ʵ�������ڵ�
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootScene;
	
	//������ʵ��ģ��������ǲ�����ģ�Ͱ�
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	//����ģ����ײΪPickupProfile
	BaseMesh->SetCollisionProfileName(FName("PickupProfile"));

	////������һ֡������
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

	////�����һ֡����,��������
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
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);		// ��Ϊ������һ֡���٣�������Ҫ�Ⱥ�����
	if (GetWorld()) GetWorld()->DestroyActor(this);
	return ObjectIndex;
}

