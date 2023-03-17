// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DemoMenuHUD.h"
#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateBasics.h"

ADemoMenuHUD::ADemoMenuHUD()
{
	if (GEngine && GEngine->GameViewport) {

		SAssignNew(MenuHUDWidget, SDemoMenuHUDWidget);

		/*
		 * Slate小部件是通过SNew和SAssignNew构造的
		 *
		 * TSharedRef<SButton> MyButton = SNew(SButton);
		 *        or
		 * TSharedPtr<SButton> MyButton;
		 * SAssignNew( MyButton, SButton );
		 *
		 * SNew(类)
		 * SAssignNe(指针, 类)
		 */
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));

	}
}
