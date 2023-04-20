// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPlayerState.h"

#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerController.h"


ADemoPlayerState::ADemoPlayerState()
{
	// 允许每帧运行
	PrimaryActorTick.bCanEverTick = true;

	//当前选中的快捷栏序号
	CurrentShortcutIndex = 0;

	//设置初始血值为500
	HP = 500.f;

	//设置初始饥饿值为600
	Hunger = 600.f;

	////没有死亡
	//IsDead = false;
}

void ADemoPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//如果控制器指针为空,添加引用
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ADemoPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//如果饥饿度为0,持续减血
	if (Hunger <= 0) 
	{
		HP -= DeltaSeconds * 2;
	}
	else 
	{
		//if (!IsDead) 
		//{
			//如果饥饿不为0,持续减饥饿度,每秒减2
			Hunger -= DeltaSeconds * 2;

			//持续加血,每秒加1
			HP += DeltaSeconds;
		//}
	}

	//设定范围
	HP = FMath::Clamp<float>(HP, 0.f, 500.f);
	Hunger = FMath::Clamp<float>(Hunger, 0.f, 600.f);

	//执行修改玩家状态UI的委托
	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);			// ExecuteIfBound  执行委托，小于500再开始降低血量与饥饿度

	////如果血值等于0但是没死
	//if (HP == 0.f && !IsDead) 
	//{
	//	//告诉控制器自己死了
	//	if (SPController) SPController->PlayerDead();
	//	IsDead = true;
	//}

}

// 提供给 ShortcutWidget 的添加快捷栏容器委托，在 GameHUD 中绑定了
void ADemoPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList); It; ++It) 
	{
		ShortcutContainerList.Add(*It);
	}

	ShortcutInfoTextAttr.BindUObject(this, &ADemoPlayerState::GetShortcutInfoText);				// 绑定	获取快捷栏物品信息 的函数

	//绑定快捷栏信息TextBolck
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	////临时测试代码,设置快捷栏的物品
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
	// 下一个被选择的容器的下标
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

	// 更新当前选择的容器Index
	CurrentShortcutIndex = NextIndex;
}

//获取选中容器内的物品的Index
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
	//绑定射线检测信息
	RayInfoTextBlock->SetText(RayInfoTextAttr);
}

int ADemoPlayerState::GetAffectRange()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	//获取当前手上物品的作用范围
	return ObjectAttr->AffectRange;
}

//根据正在撸的资源的类型以及手持物品的类型来返回伤害
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
	//更改快捷栏信息
	ShortcutContainerList[ShortcutID]->SetObject(ObjectID)->SetObjectNum(ObjectNum);

	//告诉controller更新一次手持物品
	SPController->ChangeHandObject();
}

void ADemoPlayerState::PromoteHunger()
{
	//只要超过500,马上设为600
	if (Hunger + 100 >= 500.f) 
	{
		Hunger = 600.f;
		return;
	}
	//否则只加100
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
//	//如果血值等于0但是没死
//	if (HP == 0 && !IsDead)
//	{
//		//告诉控制器自己死了
//		if (SPController) SPController->PlayerDead();
//		IsDead = true;
//	}
//}
//
//void ADemoPlayerState::LoadState(float HPVal, float HungerVal)
//{
//	HP = HPVal;
//	Hunger = HungerVal;
//	//执行修改玩家状态UI的委托
//	UpdateStateWidget.ExecuteIfBound(HP / 500.f, Hunger / 500.f);
//}
//
//void ADemoPlayerState::SaveState(float& HPVal, float& HungerVal)
//{
//	HPVal = HP;
//	HungerVal = Hunger;
//}

// 获取快捷栏物品信息
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
