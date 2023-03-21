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

	//获取MenuStyle
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
					.Padding(FMargin(20.f, 0.f, 0.f, 0.f))	// Padding 的4个值分别对应 左 上 右 下
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
	//获取输入的新存档名
	FText InputText = EditTextBox->GetText();

	//文字是否为空
	if (InputText.ToString().IsEmpty()) return false;

	//查询是否存在存档
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It) 
	{
		if ((*It).Equals(InputText.ToString()))			//判断存档名是否重复，Equals 按字典顺序测试此字符串是否等同于给定的Other字符串
		{
			//设置TextBox为空
			EditTextBox->SetText(FText::FromString(""));
			//修改Hint为存档名重复
			EditTextBox->SetHintText(NSLOCTEXT("DemoMenu", "NameRepeatedHint", "Record Name Repeated!"));
			
			return false;
		}
	}
	//保存新的存档名
	DemoDataHandle::Get()->RecordName = InputText.ToString();

	return true;
}
