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

	//获取物品信息
	FText GetInfoText() const;

	//被拾取,返回物品ID
	int TakePickup();

public:
	// 物品ID
	int ObjectIndex;

	//是否下一帧销毁
	bool IsDestroyNextTick;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//根组件
	USceneComponent* RootScene;

	//静态模型
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
};
