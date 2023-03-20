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

	// ��ȡ MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");

	// ��ȡί��
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(500.f)
			.HeightOverride(300.f)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()				// ����ͼƬ
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

					// ��һ��
					+SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.f)		// ���߶�
					[
						SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()		// ����ѡ��1
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						.FillWidth(1.f)							//�����
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

						+ SHorizontalBox::Slot()		// ����ѡ��2
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


					//�ڶ���
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillHeight(1.f)
					[
						SNew(SOverlay)

						+ SOverlay::Slot()					// �������������
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock)
								.Font(MenuStyle->Font_40)
								.ColorAndOpacity(MenuStyle->FontColor_Black)
								.Text(NSLOCTEXT("DemoMenu", "Music", "Music"))
							]

						+ SOverlay::Slot()					// ������
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SBox)
							.WidthOverride(240.f)					// ���������
							[
								SNew(SOverlay)                      

								+ SOverlay::Slot()					// ��ͼ������
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								.Padding(FMargin(30.f, 0.f))
								[
									SNew(SImage)
									.Image(&MenuStyle->SliderBarBrush)
								]

								+ SOverlay::Slot()					// ������
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Center)
								[
									SAssignNew(MuSlider, SSlider)
									.Style(&MenuStyle->SliderStyle)
									.OnValueChanged(this, &SDemoGameOptionWidget::MusicSliderChanged)		// OnValueChanged ���б仯ʱ���е�ί��,���ҽ���ǰֵ���뷽��
								]
							]
						]

						+ SOverlay::Slot()				// �������ٷְ�����
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						[
							SAssignNew(MuTextBlock, STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
						]
					]


					//������
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
	////���� ZhCheckBox ��ʽ
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);				// δѡ��ʱ����ͼƬ
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);		// δѡ��ʱ������ƶ�������ʱ��ͼƬ
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);		// δѡ��ʱ����갴��ʱ��ͼƬ
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);					// ѡ��ʱ����ͼƬ
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);			// ѡ��ʱ������ƶ�������ʱ��ͼƬ
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);			// ѡ��ʱ����갴��ʱ��ͼƬ

	//���� EnCheckBox ��ʽ
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	// ����ʱ��������һ��ѡ�У���DataHandle��ȡ������
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
	// ���� ���� ��Ч �ı��İٷֱ�
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(DemoDataHandle::Get()->MusicVolume * 100)) + FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(DemoDataHandle::Get()->SoundVolume * 100)) + FString("%")));

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


//����CheckBox�¼�
void SDemoGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//���ñ�ѡ�еĿ�
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//�������ݿ�����ת��Ϊ����
	//DemoDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);			// ExecuteIfBound ִ��ί��(û̫�����ף����ί����ô�ĵ�ֵ)
}

//Ӣ��CheckBox�¼�
void SDemoGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//���ñ�ѡ�еĿ�
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//�������ݿ�����ת��Ϊ����
	//DemoDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}

// �����仯�¼� ����
void SDemoGameOptionWidget::MusicSliderChanged(float Value)
{
	//��ʾ�ٷֱȣ� RoundToInt ȡ��
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));

	//�޸�����
	//DemoDataHandle::Get()->ResetMenuVolume(Value, -1.f);
	ChangeVolume.ExecuteIfBound(Value, -1.f);
}

// �����仯�¼� ��Ч
void SDemoGameOptionWidget::SoundSliderChanged(float Value)
{
	//��ʾ�ٷֱ�
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//�޸�����
	//DemoDataHandle::Get()->ResetMenuVolume(-1.f, Value);
	ChangeVolume.ExecuteIfBound(-1.f, Value);
}
