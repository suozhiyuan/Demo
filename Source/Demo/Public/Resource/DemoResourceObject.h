// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "GameFramework/Actor.h"
#include "DemoResourceObject.generated.h"

UCLASS()
class DEMO_API ADemoResourceObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoResourceObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//��ȡ��Ʒ��Ϣ
	FText GetInfoText() const;

	//��ȡ��Դ����
	EResourceType::Type GetResourceType();

	//��ȡѪ���ٷֱ�
	float GetHPRange();

	// ���˺����룬Ѫ������
	ADemoResourceObject* TakeObjectDamage(int Damage);

public:
	//��ԴID
	int ResourceIndex;

	//�Ƿ�����һ֡����
	bool IsDestroyNextTick;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//	//���ɵ�����
//	void CreateFlobObject();

protected:

	//�����
	USceneComponent* RootScene;

	//��̬ģ��
	UStaticMeshComponent* BaseMesh;

	//������Դ��ַ,�������ˢ��Դ
	TArray<FString> ResourcePath;

	//Ѫ��
	int HP;

	//����Ѫ��
	int BaseHP;

};
