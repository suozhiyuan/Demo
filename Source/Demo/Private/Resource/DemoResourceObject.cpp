// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource/DemoResourceObject.h"

// Sets default values
ADemoResourceObject::ADemoResourceObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ʵ�������ڵ�
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//ʵ����ģ�����
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));		// ������ײ

	//�����������
	BaseMesh->SetGenerateOverlapEvents(true);

	////��������һ֡������
	//IsDestroyNextTick = false;
}

// Called when the game starts or when spawned
void ADemoResourceObject::BeginPlay()
{
	Super::BeginPlay();
	//TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//HP = BaseHP = ResourceAttr->HP;

}

//void ADemoResourceObject::CreateFlobObject()
//{
//	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
//	//�������ɵ�����
//	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It) {
//		//������ɵ�����
//		FRandomStream Stream;
//		Stream.GenerateNewSeed();
//		//��������
//		int Num = Stream.RandRange((*It)[1], (*It)[2]);
//
//		if (GetWorld()) {
//			for (int i = 0; i < Num; ++i) {
//				//���ɵ�����
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

	////�����⵽��һ֡Ҫ����
	//if (IsDestroyNextTick) GetWorld()->DestroyActor(this);

}


//FText ADemoResourceObject::GetInfoText() const
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
//EResourceType::Type ADemoResourceObject::GetResourceType()
//{
//	TSharedPtr<ResourceAttribute> ResourceAttr = *DemoDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
//	return ResourceAttr->ResourceType;
//}
//
//float ADemoResourceObject::GetHPRange()
//{
//	return FMath::Clamp<float>((float)HP / (float)BaseHP, 0.f, 1.f);
//}
//
//ADemoResourceObject* ADemoResourceObject::TakeObjectDamage(int Damage)
//{
//	HP = FMath::Clamp<int>(HP - Damage, 0, BaseHP);
//
//	if (HP <= 0) {
//		//���ʧЧ
//		BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
//		//����������
//		CreateFlobObject();
//		//��������
//		GetWorld()->DestroyActor(this);
//	}
//	return this;
//}
//
