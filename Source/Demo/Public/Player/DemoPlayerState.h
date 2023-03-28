// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/DemoType.h"
#include "DemoPlayerState.generated.h"



//class STextBlock;

////�������״̬UIί��
//DECLARE_DELEGATE_TwoParams(FUpdateStateWidget, float, float)


/**
 *
 */
UCLASS()
class DEMO_API ADemoPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADemoPlayerState();

//	virtual void Tick(float DeltaSeconds) override;

	//�ṩ�� ShortcutWidget ����ӿ��������ί��
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);

	//�л������
	void ChooseShortcut(bool IsPre);

	//��ȡѡ�������ڵ���Ʒ��Index
	int GetCurrentHandObjectIndex() const;

	//��ȡ��ǰ�ֳ���Ʒ����Ʒ����
	EObjectType::Type GetCurrentObjectType();

	//�ṩ��RayInfowidget��ע��������Ϣ�¼�
	void RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock);

	//��ȡ������Ʒ�Ĺ�����Χ
	int GetAffectRange();

	//��ȡ�˺�ֵ
	int GetDamageValue(EResourceType::Type ResourceType);

//	//���Ŀ������Ʒ��Ϣ
//	void ChangeHandObject(int ShortcutID, int ObjectID, int ObjectNum);
//
//	//��������ֵ
//	void PromoteHunger();
//
//	//�Ƿ��Ѿ�����
//	bool IsPlayerDead();
//
//	//�����˺�
//	void AcceptDamage(int DamageVal);
//
//	//����Ѫ���ͼ�����
//	void LoadState(float HPVal, float HungerVal);
//
//	//����Ѫ���ͼ���ֵ��ָ������
//	void SaveState(float& HPVal, float& HungerVal);
//

public:
	//��ǰ��ѡ�еĿ�������
	int CurrentShortcutIndex;

	//���߼����ϢText,��PlayerController���и���
	FText RayInfoText;

//	//�������״̬UI,�󶨵ķ�����PlayerStateWidget��UpdateStateWidget
//	FUpdateStateWidget UpdateStateWidget;
//
//	//��ȡ������ָ��
//	class ADemoPlayerController* SPController;
//
//protected:
//
//	virtual void BeginPlay() override;
//
//
private:
	//��ȡ�������Ʒ��Ϣ
	FText GetShortcutInfoText() const;

	//��ȡ���߼����Ϣ
	FText GetRayInfoText() const;

private:

	//���������
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	//�������Ϣ����. TAttribute �󶨵ĺ�����������������ֵ�޸�ʱ���Լ�ͬʱҲ���޸�
	TAttribute<FText> ShortcutInfoTextAttr;

	//������Ϣ����
	TAttribute<FText> RayInfoTextAttr;

//	//Ѫֵ������
//	float HP;
//	float Hunger;
//
//	//�Ƿ��Ѿ�����
//	bool IsDead;

};
