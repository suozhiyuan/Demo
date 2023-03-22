// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuWidget.h"
#include "SlateOptMacros.h"
#include "Common/DemoHelper.h"
#include "Data/DemoDataHandle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Data/DemoType.h"
#include "GamePlay/DemoMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/SDemoGameOptionWidget.h"
#include "UI/Widget/SDemoNewGameWidget.h"
#include "UI/Widget/SDemoChooseRecordWidget.h"
#include "UI/Widget/SDemoMenuItemWidget.h"

struct MenuGroup
{
	//�˵�����
	FText MenuName;

	//�˵��߶�
	float MenuHeight;

	//�������
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;

	//���캯��
	MenuGroup(const FText Name, const float Height, TArray<TSharedPtr<SCompoundWidget>>* Children)
	{
		MenuName = Name;
		MenuHeight = Height;
		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children); It; ++It)
		{
			ChildWidget.Add(*It);
		}
	}
};

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoMenuWidget::Construct(const FArguments& InArgs)
{


	//��ȡMenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");					//��ȡ�༭���� MenuStyle
	////���ű�������
	//FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);

	//FInternationalization::Get().SetCurrentLanguage(TEXT("en"));
	//FInternationalization::Get().SetCurrentLanguage(TEXT("zh"));

	ChildSlot
		[
			SAssignNew(RootSizeBox, SBox)		// SBox û��Slot ��û�� Slot Ҫô���ܲ����������Ҫôֻ�ܲ���1�������������ֻ�ܲ���1��Image
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(FMargin(0.f, 50.f, 0.f, 0.f))		// �Ϸ�Ҫ�ű��⣬���¼��
					[
						SNew(SImage)
						.Image(&MenuStyle->MenuBackgroundBrush)
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->LeftIconBrush)
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->RightIconBrush)
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					[
						SNew(SBox)
						.WidthOverride(400.f)
						.HeightOverride(100.f)
						[
							SNew(SBorder)		// ��ΪImage�²��ܷ��ӿؼ�������ѡ��SBorder
							.BorderImage(&MenuStyle->TitleBorderBrush)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								SAssignNew(TitleText, STextBlock)			// �ı��ӿؼ�
								.Font(DemoStyle::Get().GetFontStyle("MenuItemFont"))
								.Font(MenuStyle->Font_60)
								.Text(NSLOCTEXT("DemoMenu", "Menu", "Menu"))
							]
						]

					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
					[
						SAssignNew(ContentBox, SVerticalBox)		// SVerticalBox һ����ֱ����塣������Ϣ��μ� SBoxPanel

						//+ SVerticalBox::Slot()
						//	[
						//		//SNew(SDemoGameOptionWidget)
						//		//.ChangeCulture(this, &SDemoMenuWidget::ChangeCulture)			// SDemoGameOptionWidget �µ�ί��
						//		//.ChangeVolume(this, &SDemoMenuWidget::ChangeVolume)			// SDemoGameOptionWidget �µ�ί��
						//	]
						///*
						// * �ڴ�ֱ�б������һ����ۣ�����Newһ�� SDemoMenuItemWidget
						// * ��ͬ���� ChildSlot ֮������д
						// * ContentBox->AddSlot()
						// * [
						// *		SNew(SDemoMenuItemWidget)
						// * ];
						// */
						//+SVerticalBox::Slot()						
						//[
						//	SNew(SDemoMenuItemWidget)
						//	.ItemText(NSLOCTEXT("DemoMenu", "StartGame", "StartGame"))
						//	.ItemType(EMenuItem::StartGame)
						//	.OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked)
						//]
					]

			]
		];
	
	InitializedMenuList();
	InitializedAnimation();
}


void SDemoMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	//TitleText->SetText(NSLOCTEXT("DemoMenu", "StartGame", "StartGame"));			// �޸ı�������
	//DemoHelper::Debug(FString("Test"), 5.f);

	//�����ס��,ֱ��return
	if (ControlLocked) return;

	//������ס�˰�ť
	ControlLocked = true;

	switch (ItemType)
	{
	case EMenuItem::StartGame:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::GameOption:
		PlayClose(EMenuType::GameOption);
		break;
	case EMenuItem::QuitGame:
		//�˳���Ϸ,��������������ʱ�����˳�����
	//	DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &DemoMenuWidget::QuitGame);
		break;
	case EMenuItem::NewGame:
		PlayClose(EMenuType::NewGame);
		break;
	case EMenuItem::LoadRecord:
		PlayClose(EMenuType::ChooseRecord);
		break;
	case EMenuItem::StartGameGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::GameOptionGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::NewGameGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::ChooseRecordGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::EnterGame:
		//����Ƿ���Խ�����Ϸ
		//if (NewGameWidget->AllowEnterGame())
		//{
		//	DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SDemoMenuWidget::EnterGame);
		//}
		//else
		//{
		//	//������ť
		//	ControlLocked = false;
		//}
		break;
	case EMenuItem::EnterRecord:
		//����ѡ��浵���´浵��
		//ChooseRecordWidget->UpdateRecordName();
		//DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SDemoMenuWidget::EnterGame);
		break;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SDemoMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	switch (AnimState)
	{
	case EMenuAnim::Stop:
		break;
	case EMenuAnim::Close:
		//������ڲ���
		if (MenuAnimation.IsPlaying())		// IsPlaying ��鶯�������Ƿ����ڲ��ţ��ڲ��ŷ���true
		{
			//ʵʱ�޸�Menu�Ĵ�С
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
			//�ڹر���40%��ʱ�����ò���ʾ���
			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);		// GetLerp() ��ȡ������0��1֮��������ڲ�ֵ��
		}
		else 
		{
			// �رն�������,����״̬Ϊ��
			AnimState = EMenuAnim::Open;
			// ��ʼ���Ŵ򿪶���
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		//������ڲ���
		if (MenuAnimation.IsPlaying())
		{
			//ʵʱ�޸�Menu��С
			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
			//��60%֮����ʾ���
			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
		}
		//����Ѿ��������
		if (MenuAnimation.IsAtEnd())		// IsAtEnd �����ж��Ƿ񲥷����
		{
			//�޸�״̬ΪStop
			AnimState = EMenuAnim::Stop;
			//������ť
			ControlLocked = false;
		}
		break;
	}
}


// �޸�����
void SDemoMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	DemoDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

// �޸�����
void SDemoMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	DemoDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

// ��ʼ�����еĿؼ�
void SDemoMenuWidget::InitializedMenuList()
{
	// ʵ����������
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;		// �������и�����ť��ʵ��
	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this, 	&SDemoMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "Menu", "Menu"), 510.f, &MainMenuList)));


	// ��ʼ��Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "StartGame", "StartGame"), 510.f, &StartGameList)));


	// ��Ϸ���ý���
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	// ʵ������Ϸ���õ�Widget
	SAssignNew(GameOptionWidget, SDemoGameOptionWidget).ChangeCulture(this, &SDemoMenuWidget::ChangeCulture).ChangeVolume(this, &SDemoMenuWidget::ChangeVolume);
	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "GameOption", "GameOption"), 610.f, &GameOptionList)));


	// ��ʼ����Ϸ����
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SDemoNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "NewGame", "NewGame"), 510.f, &NewGameList)));

	// ѡ��浵����
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SDemoChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));

	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList)));

	// ��ʱѡ�����˵�
	ChooseWidget(EMenuType::MainMenu);
}

// ����ѡ����ʾ�Ľ���
void SDemoMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	//�����Ƿ��Ѿ���ʾ�˵�
	IsMenuShow = WidgetType != EMenuType::None;

	// �Ƴ��������
	ContentBox->ClearChildren();

	// ��� Menutype �� None
	if (WidgetType == EMenuType::None) return;

	// ѭ��������
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It) 
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];			// ��ͷ�ú������
	}

	// ���ı���
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);

	// ��ʱ�޸ĸ߶�
	ResetWidgetSize(600.f, (*MenuMap.Find(WidgetType))->MenuHeight);
}

// �޸Ĳ˵��Ĵ�С��������޸ĸ߶ȣ�NewHeightת��-1
void SDemoMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
{
	RootSizeBox->SetWidthOverride(NewWidget);
	if (NewHeight < 0) return;
	RootSizeBox->SetHeightOverride(NewHeight);
}

// ��ʼ���������
void SDemoMenuWidget::InitializedAnimation()
{
	//��ʼ��ʱ
	const float StartDelay = 0.3f;

	//����ʱ��
	const float AnimDuration = 0.6f;

	/**
	 * 	FCurveSequence() һ���������У�����������С������ Animination��
	 * 	������playʱ����ʱ��ע�ᱻ����
	 * 	�����е�ÿ�����߶���һ��ʱ��ƫ�ƺͳ���ʱ�䣬��ʹ�� FCurveSequence ���Է������������Ķ�����
	 */
	MenuAnimation = FCurveSequence();

	/**
	 * .AddCurve���ڸ�����ʱ���ƫ�������һ���µ����ߡ�
	 * ����1 ��ʱ��ʼ�����ߡ�
	 * ����2 �������߳����˶೤ʱ�䡣
	 * ����3 ���ڴ����ߵĻ��ͺ�����Ĭ��Ϊ���ԡ���Ҫ����Ϊƽ�������Ĺ��ɡ�
	 */
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);

	//��ʼ����Menu��С
	ResetWidgetSize(600.f, 510.f);

	//��ʼ��ʾ������
	ChooseWidget(EMenuType::MainMenu);

	//��������ť
	ControlLocked = false;

	//���ö���״̬Ϊֹͣ
	AnimState = EMenuAnim::Stop;

	//���ö���������������β,Ҳ����1
	MenuAnimation.JumpToEnd();
}

// ���Źرն���
void SDemoMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	//�����µĽ���
	CurrentMenu = NewMenu;

	//�����¸߶�
	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;

	//���ò���״̬��Close��Tick �������ڲ�ͣ�ж� EMenuAnim ��ֵ
	AnimState = EMenuAnim::Close;

	//���ŷ��򶯻����˵��л�ʱ�Ȳ��ŵĹرն���
	MenuAnimation.PlayReverse(this->AsShared());

	////�����л��˵�����
	//FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
}

//void SDemoMenuWidget::QuitGame()
//{
//	Cast<ADemoMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
//}
//
//void SDemoMenuWidget::EnterGame()
//{
//	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
//}
