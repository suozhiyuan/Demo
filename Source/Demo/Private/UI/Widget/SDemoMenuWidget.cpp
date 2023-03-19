// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuWidget::Construct(const FArguments& InArgs)
{


	//��ȡMenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");					//��ȡ�༭���� MenuStyle
	////���ű�������
	//FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);


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
								//.Text(NSLOCTEXT("DemoMenu", "Menu", "Menu"))
								.Text(FText::FromString("ABC"))
							]
						]
				    
					]

				//+ SOverlay::Slot()
				//	.HAlign(HAlign_Center)
				//	.VAlign(VAlign_Top)
				//	.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
				//	[
				//		SAssignNew(ContentBox, SVerticalBox)

				//	]

			]
		];

	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);


	//InitializedMenuList();

	//InitializedAnimation();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//
//void SSlAiMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//	switch (AnimState)
//	{
//	case EMenuAnim::Stop:
//		break;
//	case EMenuAnim::Close:
//		//������ڲ���
//		if (MenuAnimation.IsPlaying()) {
//			//ʵʱ�޸�Menu�Ĵ�С
//			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
//			//�ڹر���40%��ʱ�����ò���ʾ���
//			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
//		}
//		else {
//			//�رն�������,����״̬Ϊ��
//			AnimState = EMenuAnim::Open;
//			//��ʼ���Ŵ򿪶���
//			MenuAnimation.Play(this->AsShared());
//		}
//		break;
//	case EMenuAnim::Open:
//		//������ڲ���
//		if (MenuAnimation.IsPlaying())
//		{
//			//ʵʱ�޸�Menu��С
//			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
//			//��60%֮����ʾ���
//			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
//		}
//		//����Ѿ��������
//		if (MenuAnimation.IsAtEnd())
//		{
//			//�޸�״̬ΪStop
//			AnimState = EMenuAnim::Stop;
//			//������ť
//			ControlLocked = false;
//		}
//		break;
//	}
//}
//
//
//void SSlAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
//{
//	//�����ס��,ֱ��return
//	if (ControlLocked) return;
//	//������ס�˰�ť
//	ControlLocked = true;
//
//	switch (ItemType)
//	{
//	case EMenuItem::StartGame:
//		PlayClose(EMenuType::StartGame);
//		break;
//	case EMenuItem::GameOption:
//		PlayClose(EMenuType::GameOption);
//		break;
//	case EMenuItem::QuitGame:
//		//�˳���Ϸ,��������������ʱ�����˳�����
//		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &SSlAiMenuWidget::QuitGame);
//		break;
//	case EMenuItem::NewGame:
//		PlayClose(EMenuType::NewGame);
//		break;
//	case EMenuItem::LoadRecord:
//		PlayClose(EMenuType::ChooseRecord);
//		break;
//	case EMenuItem::StartGameGoBack:
//		PlayClose(EMenuType::MainMenu);
//		break;
//	case EMenuItem::GameOptionGoBack:
//		PlayClose(EMenuType::MainMenu);
//		break;
//	case EMenuItem::NewGameGoBack:
//		PlayClose(EMenuType::StartGame);
//		break;
//	case EMenuItem::ChooseRecordGoBack:
//		PlayClose(EMenuType::StartGame);
//		break;
//	case EMenuItem::EnterGame:
//		//����Ƿ���Խ�����Ϸ
//		if (NewGameWidget->AllowEnterGame())
//		{
//			SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
//		}
//		else
//		{
//			//������ť
//			ControlLocked = false;
//		}
//		break;
//	case EMenuItem::EnterRecord:
//		//����ѡ��浵���´浵��
//		ChooseRecordWidget->UpdateRecordName();
//		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
//		break;
//	}
//}
//
//void SSlAiMenuWidget::ChangeCulture(ECultureTeam Culture)
//{
//	SlAiDataHandle::Get()->ChangeLocalizationCulture(Culture);
//}
//
//void SSlAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
//{
//	SlAiDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
//}
//
//void SSlAiMenuWidget::InitializedMenuList()
//{
//
//	//ʵ����������
//	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
//	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	MainMenuList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "Menu", "Menu"), 510.f, &MainMenuList)));
//
//
//	//��ʼ��Ϸ����
//	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
//	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	StartGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"), 510.f, &StartGameList)));
//
//
//	//��Ϸ���ý���
//	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
//	//ʵ������Ϸ���õ�Widget
//	SAssignNew(GameOptionWidget, SSlAiGameOptionWidget)
//		.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
//		.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume);
//	//��ӿؼ�������
//	GameOptionList.Add(GameOptionWidget);
//	GameOptionList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption"), 610.f, &GameOptionList)));
//
//
//	//��ʼ����Ϸ����
//	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
//	SAssignNew(NewGameWidget, SSlAiNewGameWidget);
//	NewGameList.Add(NewGameWidget);
//	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	NewGameList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"), 510.f, &NewGameList)));
//
//	//ѡ��浵����
//	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
//	SAssignNew(ChooseRecordWidget, SSlAiChooseRecordWidget);
//	ChooseRecordList.Add(ChooseRecordWidget);
//	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList)));
//
//
//}
//
//void SSlAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
//{
//	//�����Ƿ��Ѿ���ʾ�˵�
//	IsMenuShow = WidgetType != EMenuType::None;
//	//�Ƴ��������
//	ContentBox->ClearChildren();
//	//���Menutype��None
//	if (WidgetType == EMenuType::None) return;
//	//ѭ��������
//	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It) {
//		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
//	}
//	//���ı���
//	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
//
//}
//
////������޸ĸ߶�,NewHeightת��-1
//void SSlAiMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
//{
//	RootSizeBox->SetWidthOverride(NewWidget);
//	if (NewHeight < 0) return;
//	RootSizeBox->SetHeightOverride(NewHeight);
//}
//
//void SSlAiMenuWidget::InitializedAnimation()
//{
//	//��ʼ��ʱ
//	const float StartDelay = 0.3f;
//	//����ʱ��
//	const float AnimDuration = 0.6f;
//	MenuAnimation = FCurveSequence();
//	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
//	//��ʼ����Menu��С
//	ResetWidgetSize(600.f, 510.f);
//	//��ʼ��ʾ������
//	ChooseWidget(EMenuType::MainMenu);
//	//��������ť
//	ControlLocked = false;
//	//���ö���״̬Ϊֹͣ
//	AnimState = EMenuAnim::Stop;
//	//���ö���������������β,Ҳ����1
//	MenuAnimation.JumpToEnd();
//}
//
//void SSlAiMenuWidget::PlayClose(EMenuType::Type NewMenu)
//{
//	//�����µĽ���
//	CurrentMenu = NewMenu;
//	//�����¸߶�
//	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
//	//���ò���״̬��Close
//	AnimState = EMenuAnim::Close;
//	//���ŷ��򶯻�
//	MenuAnimation.PlayReverse(this->AsShared());
//	//�����л��˵�����
//	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
//}
//
//void SSlAiMenuWidget::QuitGame()
//{
//	Cast<ASlAiMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
//}
//
//void SSlAiMenuWidget::EnterGame()
//{
//	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
//}
