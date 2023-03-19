// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "Widgets/Layout/SDPIScaler.h"
#include "UI/Widget/SDemoMenuWidget.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuHUDWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");			//��ȡ�༭����MenuStyle

	//�����Ź��򷽷�
	UIScaler.Bind(this, &SDemoMenuHUDWidget::GetUIScaler);

	ChildSlot
		[
			SNew(SDPIScaler)
			.DPIScale(UIScaler)										// ��һ�㼶���е����������� UIScaler ��ֵ��������
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuHUDBackgroundBrush)	// ʵ����һ��Image��������Image�������һ����ˢ
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MenuWidget, SDemoMenuWidget)
					]

				// //�������ԣ�ͨ��FOverlaySlot����������޸�
				//+ SOverlay::Slot()
				//	.HAlign(HAlign_Left)
				//	.VAlign(VAlign_Top)
				//	.Expose(ImageSlot)				// ��ImageSlot
				//	[
				//		SNew(SButton)
				//		.OnClicked(this, &SDemoMenuHUDWidget::OnClick)
				//	]
			]
		];
}

//��UIScaler�ĺ���
float SDemoMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

//��ȡ��Ļ�ߴ�
FVector2D SDemoMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(Result);
	return Result;
}

//FReply SDemoMenuHUDWidget::OnClick()
//{
//	ImageSlot->HAlign(HAlign_Right).VAlign(VAlign_Bottom);
//	return FReply::Handled();			// һ���¼�Ӧ�÷���һ��FReply:: Handled����ϵͳ֪��һ���¼��������ˡ�
//}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
