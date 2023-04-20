// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerState.h"

#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerController.h"


ADemoPlayerState::ADemoPlayerState()
{
	// ����ÿ֡����
	PrimaryActorTick.bCanEverTick = true;

	//��ǰѡ�еĿ�������
	CurrentShortcutIndex = 0;

	//���ó�ʼѪֵΪ500
	HP = 500.f;

	//���ó�ʼ����ֵΪ600
	Hunger = 600.f;

	////û������
	//IsDead = false;
}

void ADemoPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//���������ָ��Ϊ��,�������
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ADemoPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//���������Ϊ0,������Ѫ
	if (Hunger <= 0) 
	{
		HP -= DeltaSeconds * 2;
	}
	else 
	{
		//if (!IsDead) 
		//{
			//���������Ϊ0,������������,ÿ���2
			Hunger -= DeltaSeconds * 2;

			//������Ѫ,ÿ���1
			HP += DeltaSeconds;
		//}
	}

	//�趨��Χ
	HP = FMath::Clamp<float>(HP, 0.f, 500.f);
	Hunger = FMath::Clamp<float>(Hunger, 0.f, 600.f);

	//ִ���޸����״̬UI��ί��
	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);			// ExecuteIfBound  ִ��ί�У�С��500�ٿ�ʼ����Ѫ���뼢����

	////���Ѫֵ����0����û��
	//if (HP == 0.f && !IsDead) 
	//{
	//	//���߿������Լ�����
	//	if (SPController) SPController->PlayerDead();
	//	IsDead = true;
	//}

}

// �ṩ�� ShortcutWidget ����ӿ��������ί�У��� GameHUD �а���
void ADemoPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList); It; ++It) 
	{
		ShortcutContainerList.Add(*It);
	}

	ShortcutInfoTextAttr.BindUObject(this, &ADemoPlayerState::GetShortcutInfoText);				// ��	��ȡ�������Ʒ��Ϣ �ĺ���

	//�󶨿������ϢTextBolck
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	////��ʱ���Դ���,���ÿ��������Ʒ
	//ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	//ShortcutContainerList[2]->SetObject(2)->SetObjectNum(15);
	//ShortcutContainerList[3]->SetObject(3)->SetObjectNum(1);
	//ShortcutContainerList[4]->SetObject(4)->SetObjectNum(35);
	//ShortcutContainerList[5]->SetObject(5)->SetObjectNum(45);
	//ShortcutContainerList[6]->SetObject(6)->SetObjectNum(55);
	//ShortcutContainerList[7]->SetObject(7)->SetObjectNum(64);
}

void ADemoPlayerState::ChooseShortcut(bool IsPre)
{
	// ��һ����ѡ����������±�
	int NextIndex = 0;

	if (IsPre)
	{
		NextIndex = CurrentShortcutIndex - 1 < 0 ? 8 : CurrentShortcutIndex - 1;
	}
	else 
	{
		NextIndex = CurrentShortcutIndex + 1 > 8 ? 0 : CurrentShortcutIndex + 1;
	}
	ShortcutContainerList[CurrentShortcutIndex]->SetChoosed(false);
	ShortcutContainerList[NextIndex]->SetChoosed(true);

	// ���µ�ǰѡ�������Index
	CurrentShortcutIndex = NextIndex;
}

//��ȡѡ�������ڵ���Ʒ��Index
int ADemoPlayerState::GetCurrentHandObjectIndex() const
{
	if (ShortcutContainerList.Num() == 0) return 0;
	return ShortcutContainerList[CurrentShortcutIndex]->ObjectIndex;
}

EObjectType::Type ADemoPlayerState::GetCurrentObjectType()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	return ObjectAttr->ObjectType;
}

void ADemoPlayerState::RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock)
{
	RayInfoTextAttr.BindUObject(this, &ADemoPlayerState::GetRayInfoText);
	//�����߼����Ϣ
	RayInfoTextBlock->SetText(RayInfoTextAttr);
}

int ADemoPlayerState::GetAffectRange()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	//��ȡ��ǰ������Ʒ�����÷�Χ
	return ObjectAttr->AffectRange;
}

//��������ߣ����Դ�������Լ��ֳ���Ʒ�������������˺�
int ADemoPlayerState::GetDamageValue(EResourceType::Type ResourceType)
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (ResourceType)
	{
	case EResourceType::Plant:
		return ObjectAttr->PlantAttack;
		break;
	case EResourceType::Metal:
		return ObjectAttr->MetalAttcck;
		break;
	case EResourceType::Animal:
		return ObjectAttr->AnimalAttack;
		break;
	}
	return ObjectAttr->PlantAttack;
}

void ADemoPlayerState::ChangeHandObject(int ShortcutID, int ObjectID, int ObjectNum)
{
	//���Ŀ������Ϣ
	ShortcutContainerList[ShortcutID]->SetObject(ObjectID)->SetObjectNum(ObjectNum);

	//����controller����һ���ֳ���Ʒ
	SPController->ChangeHandObject();
}

void ADemoPlayerState::PromoteHunger()
{
	//ֻҪ����500,������Ϊ600
	if (Hunger + 100 >= 500.f) 
	{
		Hunger = 600.f;
		return;
	}
	//����ֻ��100
	Hunger = FMath::Clamp<float>(Hunger + 100.f, 0, 600.f);
}

bool ADemoPlayerState::IsPlayerDead()
{
	return HP <= 0.f;
}

//void ADemoPlayerState::AcceptDamage(int DamageVal)
//{
//	HP = FMath::Clamp<float>(HP - DamageVal, 0.f, 500.f);
//	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);
//	//���Ѫֵ����0����û��
//	if (HP == 0 && !IsDead)
//	{
//		//���߿������Լ�����
//		if (SPController) SPController->PlayerDead();
//		IsDead = true;
//	}
//}
//
//void ADemoPlayerState::LoadState(float HPVal, float HungerVal)
//{
//	HP = HPVal;
//	Hunger = HungerVal;
//	//ִ���޸����״̬UI��ί��
//	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);
//}
//
//void ADemoPlayerState::SaveState(float& HPVal, float& HungerVal)
//{
//	HPVal = HP;
//	HungerVal = Hunger;
//}

// ��ȡ�������Ʒ��Ϣ
FText ADemoPlayerState::GetShortcutInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (DemoDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
	}
	return ObjectAttr->ZH;
}

FText ADemoPlayerState::GetRayInfoText() const
{
	return RayInfoText;
}
