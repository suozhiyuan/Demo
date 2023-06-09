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

	//生成物品初始化
	void CreateFlobObject(int ObjectID);

	//丢弃物品初始化,丢弃的物品ID和丢弃方向
	void ThrowFlobObject(int ObjectID, float DirYaw);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	//渲染贴图
	void RenderTexture();

	//动态检测事件
	void DetectPlayer();

	//销毁事件
	void DestroyEvent();

private:

	class UBoxComponent* BoxCollision;			// 用一个 Box 做根组件

	class UStaticMeshComponent* BaseMesh;		// 静态模型

	//物品ID
	int ObjectIndex;

	// 贴图路径
	class UTexture* ObjectIconTex;

	// 动态材质实例
	class UMaterialInstanceDynamic* ObjectIconMatDynamic;

	//玩家指针
	class ADemoPlayerCharacter* SPCharacter;

	//动态检测玩家的时间
	FTimerHandle DetectTimer;

	//掉落资源销毁时间Timer
	FTimerHandle DestroyTimer;

};
