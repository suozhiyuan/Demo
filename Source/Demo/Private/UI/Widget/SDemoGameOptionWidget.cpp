// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoStyle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "Widgets/Images/SImage.h"
#include "Data/DemoDataHandle.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/STextBlock.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoGameOptionWidget::Construct(const FArguments& InArgs)
{

	// 获取 MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");

	// 获取委托
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(500.f)
			.HeightOverride(300.f)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()				// 背景图片
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&MenuStyle->GameOptionBGBrush)
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(50.f))
				[
					SNew(SVerticalBox)

					// 第一行
					+SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.f)		// 填充高度
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()		// 语言选项1
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.FillWidth(1.f)							//填充宽度
						[
							SAssignNew(ZhCheckBox, SCheckBox)
							.OnCheckStateChanged(this, &SDemoGameOptionWidget::ZhCheckBoxStateChanged)
							[
								SNew(STextBlock)
								.Font(DemoStyle::Get().GetFontStyle("MenuItemFont"))
								.Font(MenuStyle->Font_40)
								.ColorAndOpacity(MenuStyle->FontColor_Black)
								.Text(NSLOCTEXT("DemoMenu", "Chinese", "Chinese"))
							]
						]

						+ SHorizontalBox::Slot()		// 语言选项2
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.FillWidth(1.f)
						[
							SAssignNew(EnCheckBox, SCheckBox)
							.OnCheckStateChanged(this, &SDemoGameOptionWidget::EnCheckBoxStateChanged)
							[
								SNew(STextBlock)
								.Font(MenuStyle->Font_40)
								.ColorAndOpacity(MenuStyle->FontColor_Black)
								.Text(NSLOCTEXT("DemoMenu", "English", "English"))
							]
						]
					]


					//第二行
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.f)
					[
						SNew(SOverlay)

						+ SOverlay::Slot()					// 滑动条左侧文字
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Font(MenuStyle->Font_40)
								.ColorAndOpacity(MenuStyle->FontColor_Black)
								.Text(NSLOCTEXT("DemoMenu", "Music", "Music"))
							]

						+ SOverlay::Slot()					// 滑动条
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
							.WidthOverride(240.f)					// 滑动条宽度
							[
								SNew(SOverlay)                      

								+ SOverlay::Slot()					// 底图滑动条
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								.Padding(FMargin(30.f, 0.f))
								[
									SNew(SImage)
									.Image(&MenuStyle->SliderBarBrush)
								]

								+ SOverlay::Slot()					// 滑动块
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								[
									SAssignNew(MuSlider, SSlider)
									.Style(&MenuStyle->SliderStyle)
									.OnValueChanged(this, &SDemoGameOptionWidget::MusicSliderChanged)		// OnValueChanged 当有变化时运行的委托,并且将当前值传入方法
								]
							]
						]

						+ SOverlay::Slot()				// 进度条百分百文字
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						[
							SAssignNew(MuTextBlock, STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
						]
					]


					//第三行
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.f)
					[
						SNew(SOverlay)

						+ SOverlay::Slot()
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("DemoMenu", "Sound", "Sound"))
						]

						+ SOverlay::Slot()
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
							.WidthOverride(240.f)
							[
								SNew(SOverlay)

								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								.Padding(FMargin(30.f, 0.f))
								[
									SNew(SImage)
									.Image(&MenuStyle->SliderBarBrush)
								]

								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								[
									SAssignNew(SoSlider, SSlider)
									.Style(&MenuStyle->SliderStyle)
								.OnValueChanged(this, &SDemoGameOptionWidget::SoundSliderChanged)
								]
							]
						]

						+ SOverlay::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						[
							SAssignNew(SoTextBlock, STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
						]
					]
				]
			]
		];

	StyleInitialize();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SDemoGameOptionWidget::StyleInitialize()
{
	////设置 ZhCheckBox 样式
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);				// 未选中时，的图片
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);		// 未选中时，鼠标移动到上面时的图片
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);		// 未选中时，鼠标按下时的图片
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);					// 选中时，的图片
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);			// 选中时，鼠标移动到上面时的图片
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);			// 选中时，鼠标按下时的图片

	//设置 EnCheckBox 样式
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	// 运行时，让其中一个选中，从DataHandle中取参数。
	switch (DemoDataHandle::Get()->CurrentCulture)
	{
		case ECultureTeam::EN:
			EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
			ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
			break;
		case ECultureTeam::ZH:
			EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
			ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
			break;
	}

	MuSlider->SetValue(DemoDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(DemoDataHandle::Get()->SoundVolume);
	// 设置 音量 音效 文本的百分比
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(DemoDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(DemoDataHandle::Get()->SoundVolume * 100)) + FString("%")));

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


//中文CheckBox事件
void SDemoGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//告诉数据控制类转换为中文
	//DemoDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);			// ExecuteIfBound 执行委托(没太看明白，这个委托怎么改的值)
}

//英文CheckBox事件
void SDemoGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//告诉数据控制类转换为中文
	//DemoDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}

// 音量变化事件 音乐
void SDemoGameOptionWidget::MusicSliderChanged(float Value)
{
	//显示百分比， RoundToInt 取整
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));

	//修改音量
	//DemoDataHandle::Get()->ResetMenuVolume(Value, -1.f);
	ChangeVolume.ExecuteIfBound(Value, -1.f);
}

// 音量变化事件 音效
void SDemoGameOptionWidget::SoundSliderChanged(float Value)
{
	//显示百分比
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//修改音量
	//DemoDataHandle::Get()->ResetMenuVolume(-1.f, Value);
	ChangeVolume.ExecuteIfBound(-1.f, Value);
}
