// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/STextComboBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoChooseRecordWidget::Construct(const FArguments& InArgs)
{

	//获取MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");


	//初始化下拉菜单数据
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It) 
	{
		OptionsSource.Add(MakeShareable(new FString(*It)));
	}

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
					.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
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
							SAssignNew(RecordComboBox, STextComboBox)
							.Font(MenuStyle->Font_30)
							.OptionsSource(&OptionsSource)
						]
					]
			]
		];

	//设置默认的选项
	RecordComboBox->SetSelectedItem(OptionsSource[0]);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

// 更新存档名
void SDemoChooseRecordWidget::UpdateRecordName()
{
	//修改存档名
	DemoDataHandle::Get()->RecordName = *RecordComboBox->GetSelectedItem().Get();
}
