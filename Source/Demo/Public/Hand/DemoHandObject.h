// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoHandObject.generated.h"

UCLASS()
class DEMO_API ADemoHandObject : public AActor
{
GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoHandObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//������ƷID������Ʒ�Ĺ�������
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);

	////�Ƿ�������
	//void ChangeOverlayDetect(bool IsOpen);

public:
	//��ƷID
	int ObjectIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ��ײ����ʱ�ķ���
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,		bool bFromSweep, const FHitResult& SweepResult);

	// ��ײ�뿪ʱ�ķ���
	UFUNCTION()
		virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:

	//�����
	class USceneComponent* RootScene;

	//��̬ģ��
	UPROPERTY(EditAnywhere, Category = "Demo")
		class UStaticMeshComponent* BaseMesh;

	//������ײ��
	UPROPERTY(EditAnywhere, Category = "Demo")
		class UBoxComponent* AffectCollision;

	//����Ʒʱ����Ч
	class USoundWave* OverlaySound;

};
