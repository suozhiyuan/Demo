// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoNewGameWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Images/SImage.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoNewGameWidget::Construct(const FArguments& InArgs)
{

	//��ȡMenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");


	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(500.f)
			.HeightOverride(100.f)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuItemBrush)
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.Padding(FMargin(20.f, 0.f, 0.f, 0.f))	// Padding ��4��ֵ�ֱ��Ӧ �� �� �� ��
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
					.Text(NSLOCTEXT("DemoMenu", "NewGame", "NewGame"))
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
					[
						SNew(SBox)
						.WidthOverride(300.f)
						.HeightOverride(60.f)
						[
							SAssignNew(EditTextBox, SEditableTextBox)
							.HintText(NSLOCTEXT("DemoMenu", "RecordNameHint", "Input Record Name!"))
							.Font(MenuStyle->Font_30)
						]
					]
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool SDemoNewGameWidget::AllowEnterGame()
{
	//��ȡ������´浵��
	FText InputText = EditTextBox->GetText();

	//�����Ƿ�Ϊ��
	if (InputText.ToString().IsEmpty()) return false;

	//��ѯ�Ƿ���ڴ浵
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It) 
	{
		if ((*It).Equals(InputText.ToString()))			//�жϴ浵���Ƿ��ظ���Equals ���ֵ�˳����Դ��ַ����Ƿ��ͬ�ڸ�����Other�ַ���
		{
			//����TextBoxΪ��
			EditTextBox->SetText(FText::FromString(""));
			//�޸�HintΪ�浵���ظ�
			EditTextBox->SetHintText(NSLOCTEXT("DemoMenu", "NameRepeatedHint", "Record Name Repeated!"));
			
			return false;
		}
	}
	//�����µĴ浵��
	DemoDataHandle::Get()->RecordName = InputText.ToString();

	return true;
}
