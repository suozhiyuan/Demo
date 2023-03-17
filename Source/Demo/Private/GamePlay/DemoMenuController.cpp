// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DemoMenuController.h"

ADemoMenuController::ADemoMenuController()
{
	bShowMouseCursor = true;			// 显示鼠标
}

void ADemoMenuController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;			// 用于设置只允许Ul响应用户输入的输入模式的数据结构。
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);		// 鼠标的显示，设置锁定在窗口里
	SetInputMode(InputMode);			// 绑定

}
