// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DemoMenuHUD.h"
#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateBasics.h"

ADemoMenuHUD::ADemoMenuHUD()
{
	if (GEngine && GEngine->GameViewport) {

		SAssignNew(MenuHUDWidget, SDemoMenuHUDWidget);

		/*
		 * SlateС������ͨ��SNew��SAssignNew�����
		 *
		 * TSharedRef<SButton> MyButton = SNew(SButton);
		 *        or
		 * TSharedPtr<SButton> MyButton;
		 * SAssignNew( MyButton, SButton );
		 *
		 * SNew(��)
		 * SAssignNe(ָ��, ��)
		 */
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));

	}
}
