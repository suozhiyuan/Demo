// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoShortcutWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoShortcutWidget::Construct(const FArguments& InArgs)
{
	//��ȡGameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	ChildSlot
		[
			SNew(SBox)				// ��������
			.WidthOverride(900.f)
			.HeightOverride(160.f)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()			// ������Ϸ�����Ʒ��Ϣ
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SAssignNew(ShortcutInfoTextBlock, STextBlock)
					.Font(GameStyle->Font_Outline_40)
					.ColorAndOpacity(GameStyle->FontColor_White)
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.f, 60.f, 0.f, 0.f))
				[
					SAssignNew(GridPanel, SUniformGridPanel)	// ���������	
				]
			]
		];

	//����û�г�ʼ������
	IsInitializeContainer = false;
}

void SDemoShortcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer)			// ��Ϊ SlateWidget ��û��BeginPlay�����ģ�����Ҫ�� Tick �ĵ�һ֡ȥ���У��Ա�֤ȥ����ί��
	{
		InitializeContainer();
		IsInitializeContainer = true;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SDemoShortcutWidget::InitializeContainer()
{
	TArray<TSharedPtr<ShortcutContainer>> ContainerList;		// ������е����� ��ɵ�����

	for (int i = 0; i < 9; ++i) 
	{
		//��������
		TSharedPtr<SBorder> ContainerBorder;			// �������һ������
		TSharedPtr<SBorder> ObjectImage;				// �����ͼ��
		TSharedPtr<STextBlock> ObjectNumText;			// �����ͼ���ϵ�����

		SAssignNew(ContainerBorder, SBorder)
		.Padding(FMargin(10.f))
		[
			SAssignNew(ObjectImage, SBorder)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 5.f, 0.f))
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		];

		//��������ӵ�����
		GridPanel->AddSlot(i, 0)		// �ڼ��� �ڼ���
		[
			ContainerBorder->AsShared()
		];

		//ʵ����һ�������ṹ��
		TSharedPtr<ShortcutContainer> Container = MakeShareable(new ShortcutContainer(ContainerBorder, ObjectImage, ObjectNumText, &GameStyle->NormalContainerBrush, &GameStyle->ChoosedContainerBrush, &DemoDataHandle::Get()->ObjectBrushList));

		//����ǵ�һ������,������Ϊѡ��״̬
		if (i == 0) Container->SetChoosed(true);

		ContainerList.Add(Container);

	}

	//��ʵ�����Ľṹ��ע��� PlayerState ����������
	RegisterShortcutContainer.ExecuteIfBound(&ContainerList, ShortcutInfoTextBlock);

}
