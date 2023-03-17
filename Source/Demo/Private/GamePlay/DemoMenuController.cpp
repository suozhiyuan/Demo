// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DemoMenuController.h"

ADemoMenuController::ADemoMenuController()
{
	bShowMouseCursor = true;			// ��ʾ���
}

void ADemoMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;			// ��������ֻ����Ul��Ӧ�û����������ģʽ�����ݽṹ��
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);		// ������ʾ�����������ڴ�����
	SetInputMode(InputMode);			// ��

}
