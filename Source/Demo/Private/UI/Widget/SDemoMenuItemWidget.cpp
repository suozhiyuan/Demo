// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuItemWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuItemWidget::Construct(const FArguments& InArgs)
{
	//��ȡMenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");


	OnClicked = InArgs._OnClicked;		// InArgs ���Ի�ȡ����ǰ�ඨ������ж���
	ItemType = InArgs._ItemType.Get();

	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(500.f)
			.HeightOverride(100.f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					.HAlign(HAlign_Fill)
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuItemBrush)
						.ColorAndOpacity(this, &SDemoMenuItemWidget::GetTintColor)	// �����ɫ�б仯������
					]

				+ SOverlay::Slot()		// ������
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(InArgs._ItemText)
						.Font(MenuStyle->Font_60)
					]
			]
		];

	//��ʼ��
	IsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


// ʵ���˼򵥵� SButton ����
FReply SDemoMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true;
	return FReply::Handled();
}

FReply SDemoMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//�����ť�����˲���OnClickedί�а��з����Ǿ�ִ��
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);			// ��굯��ʱ�����¼��� ExecuteIfBound �ж��Ƿ�󶨣����˾�ִ��
	}
	return FReply::Handled();
}

void SDemoMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = false;
}

FSlateColor SDemoMenuItemWidget::GetTintColor() const
{
	if (IsMouseButtonDown) return FLinearColor(1.f, 0.1f, 0.1f, 0.5f);
	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
