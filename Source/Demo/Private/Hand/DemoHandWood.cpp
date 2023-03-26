// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/DemoHandWood.h"
#include "Components/BoxComponent.h"


ADemoHandWood::ADemoHandWood() :Super()
{

	//��ģ����������ģ��
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeLog_01.SM_Env_TreeLog_01'"));
	//��ģ�͵�Mesh���
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -20.f, 0.f));

	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));

}

//������ʵ�����������ΪҪ��DataHandle�ڹ��캯����������Ϣ�������
void ADemoHandWood::BeginPlay()
{
	Super::BeginPlay();

	//������Ʒ���
	ObjectIndex = 1;

}