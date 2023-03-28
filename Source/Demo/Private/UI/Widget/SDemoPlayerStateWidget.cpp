// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoPlayerStateWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoPlayerStateWidget::Construct(const FArguments& InArgs)
{

	//��ȡGameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");


	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(744.f)
			.HeightOverride(244.f)
			[
				SNew(SOverlay)

				//״̬����ͼƬ
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PlayerStateBGBrush)
				]

				//��ӽ�������CanvasPanel
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SConstraintCanvas)		// ��ӦUMG CanvasPanel

					//Ѫ��
					+ SConstraintCanvas::Slot()
					.Anchors(FAnchors(0.f))		//����ê��Ϊ���Ͻ�
					.Offset(FMargin(442.3f, 90.f, 418.f, 42.f))		//ê��Ϊ���Ͻǵ�ʱ����൱������λ�úʹ�С
					[
						SAssignNew(HPBar, SProgressBar)					// ������
						.BackgroundImage(&GameStyle->EmptyBrush)		// ����ͼƬ
						.FillImage(&GameStyle->HPBrush)					// ����ͼƬ
						.FillColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))		// �����ɫ
						.Percent(1.f)									// ����ȷ�������������λ�ã���ΧΪ0..1
					]

					//������
					+ SConstraintCanvas::Slot()
					.Anchors(FAnchors(0.f))
					.Offset(FMargin(397.5f, 145.f, 317.f, 26.f))
					[
						SAssignNew(HungerBar, SProgressBar)
						.BackgroundImage(&GameStyle->EmptyBrush)
						.FillImage(&GameStyle->HungerBrush)
						.FillColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))
						.Percent(1.f)
					]


				]

				//�������ͷ�񱳾���ͷ���Overlay
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.f, 0.f, 500.f, 0.f))
				[
					SNew(SOverlay)

					+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&GameStyle->PlayerHeadBGBrush)
					]

					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SImage)
						.Image(&GameStyle->PlayerHeadBrush)
					]
				]
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoPlayerStateWidget::UpdateStateWidget(float HPValue, float HungerValue)
{
	if (HPValue > 0) HPBar->SetPercent(FMath::Clamp<float>(HPValue, 0.f, 1.f));
	if (HungerValue > 0) HungerBar->SetPercent(FMath::Clamp<float>(HungerValue, 0.f, 1.f));
}
