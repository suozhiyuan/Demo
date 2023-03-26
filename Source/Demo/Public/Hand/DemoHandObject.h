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

	//根据物品ID返回物品的工厂方法
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);

	////是否允许检测
	//void ChangeOverlayDetect(bool IsOpen);

public:
	//物品ID
	int ObjectIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 碰撞交互时的方法
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,		bool bFromSweep, const FHitResult& SweepResult);

	// 碰撞离开时的方法
	UFUNCTION()
		virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:

	//根组件
	class USceneComponent* RootScene;

	//静态模型
	UPROPERTY(EditAnywhere, Category = "Demo")
		class UStaticMeshComponent* BaseMesh;

	//盒子碰撞体
	UPROPERTY(EditAnywhere, Category = "Demo")
		class UBoxComponent* AffectCollision;

	//打到物品时的音效
	class USoundWave* OverlaySound;

};
