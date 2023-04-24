// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTool/DemoEnemyTool.h"

#include "Components/BoxComponent.h"
#include "EnemyTool/DemoEnemySheild.h"
#include "EnemyTool/DemoEnemyWeapon.h"

// Sets default values
ADemoEnemyTool::ADemoEnemyTool()
{
	//ʵ�������ڵ�
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootScene;

	//������ʵ��ģ��������ǲ�����ģ�Ͱ�
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	//ʵ����ײ���
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(BaseMesh);
	AffectCollision->SetCollisionProfileName(FName("EnemyToolProfile"));
	//��ʼʱ�ر�Overlay���
	AffectCollision->SetGenerateOverlapEvents(false);

	//�󶨼�ⷽ������ײ��
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);//�󶨼�ⷽ������ײ��
}

void ADemoEnemyTool::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->SetGenerateOverlapEvents(IsOpen);
}

TSubclassOf<AActor> ADemoEnemyTool::SpawnEnemyWeapon()
{
	return ADemoEnemyWeapon::StaticClass();
}

TSubclassOf<AActor> ADemoEnemyTool::SpawnEnemySheild()
{
	return ADemoEnemySheild::StaticClass();
}

void ADemoEnemyTool::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ADemoEnemyTool::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

