// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DemoPickupObject.generated.h"

UCLASS()
class DEMO_API ADemoPickupObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADemoPickupObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//��ȡ��Ʒ��Ϣ
	FText GetInfoText() const;

	//��ʰȡ,������ƷID
	int TakePickup();

public:
	// ��ƷID
	int ObjectIndex;

	//�Ƿ���һ֡����
	bool IsDestroyNextTick;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//�����
	USceneComponent* RootScene;

	//��̬ģ��
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
};
