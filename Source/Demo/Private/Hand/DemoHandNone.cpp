// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/DemoHandNone.h"
#include "Components/BoxComponent.h"

ADemoHandNone::ADemoHandNone()
{
	//���ð�ģ��


	//������ײ������
	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ADemoHandNone::BeginPlay()
{
	Super::BeginPlay();

	//������Ʒ���
	ObjectIndex = 0;
}
