// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoFlobObject.generated.h"

UCLASS()
class DEMO_API ADemoFlobObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoFlobObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������Ʒ��ʼ��
	void CreateFlobObject(int ObjectID);

	////������Ʒ��ʼ��,��������ƷID�Ͷ�������
	//void ThrowFlobObject(int ObjectID, float DirYaw);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	//��Ⱦ��ͼ
	void RenderTexture();

	//��̬����¼�
	void DetectPlayer();

	//�����¼�
	void DestroyEvent();

private:

	class UBoxComponent* BoxCollision;			// ��һ�� Box �������

	class UStaticMeshComponent* BaseMesh;		// ��̬ģ��

	//��ƷID
	int ObjectIndex;

	// ��ͼ·��
	class UTexture* ObjectIconTex;

	// ��̬����ʵ��
	class UMaterialInstanceDynamic* ObjectIconMatDynamic;

	//���ָ��
	class ADemoPlayerCharacter* SPCharacter;

	//��̬�����ҵ�ʱ��
	FTimerHandle DetectTimer;

	//������Դ����ʱ��Timer
	FTimerHandle DestroyTimer;

};
