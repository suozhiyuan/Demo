// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMenuWidget.h"
#include "SlateOptMacros.h"
#include "Data/DemoDataHandle.h"
#include "UI/Style/DemoMenuWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Data/DemoType.h"
#include "UI/Widget/SDemoGameOptionWidget.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMenuWidget::Construct(const FArguments& InArgs)
{


	//获取MenuStyle
	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");					//获取编辑器的 MenuStyle
	////播放背景音乐
	//FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);

	//FInternationalization::Get().SetCurrentLanguage(TEXT("en"));
	//FInternationalization::Get().SetCurrentLanguage(TEXT("zh"));

	ChildSlot
		[
			SAssignNew(RootSizeBox, SBox)		// SBox 没有Slot ，没有 Slot 要么不能插入子组件，要么只能插入1个子组件，比如只能插入1个Image
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(FMargin(0.f, 50.f, 0.f, 0.f))		// 上方要放标题，往下间隔
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
							SNew(SBorder)		// 因为Image下不能放子控件，所以选择SBorder
							.BorderImage(&MenuStyle->TitleBorderBrush)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								SAssignNew(TitleText, STextBlock)			// 文本子控件
								.Font(DemoStyle::Get().GetFontStyle("MenuItemFont"))
								.Font(MenuStyle->Font_60)
								.Text(NSLOCTEXT("DemoMenu", "Menu", "Menu"))
								//.Text(FText::FromString("ABC"))
							]
						]

					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					.Padding(FMargin(0.f, 130.f, 0.f, 0.f))
					[
						SAssignNew(ContentBox, SVerticalBox)		// SVerticalBox 一个垂直框面板。更多信息请参见 SBoxPanel
						+ SVerticalBox::Slot()
							[
								SNew(SDemoGameOptionWidget)
								.ChangeCulture(this, &SDemoMenuWidget::ChangeCulture)			// SDemoGameOptionWidget 下的委托
								.ChangeVolume(this, &SDemoMenuWidget::ChangeVolume)			// SDemoGameOptionWidget 下的委托
							]
						///*
						// * 在垂直列表中添加一个插槽，并且New一个 SDemoMenuItemWidget
						// * 等同于在 ChildSlot 之外这样写
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

	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);


	//InitializedMenuList();

	//InitializedAnimation();
}


void SDemoMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	//TitleText->SetText(NSLOCTEXT("DemoMenu", "StartGame", "StartGame"));			// 修改标题文字
	//DemoHelper::Debug(FString("Test"), 5.f);


	////如果锁住了,直接return
	//if (ControlLocked) return;
	////设置锁住了按钮
	//ControlLocked = true;

	//switch (ItemType)
	//{
	//case EMenuItem::StartGame:
	//	PlayClose(EMenuType::StartGame);
	//	break;
	//case EMenuItem::GameOption:
	//	PlayClose(EMenuType::GameOption);
	//	break;
	//case EMenuItem::QuitGame:
	//	//退出游戏,播放声音并且延时调用退出函数
	//	DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->ExitGameSound, this, &DemoMenuWidget::QuitGame);
	//	break;
	//case EMenuItem::NewGame:
	//	PlayClose(EMenuType::NewGame);
	//	break;
	//case EMenuItem::LoadRecord:
	//	PlayClose(EMenuType::ChooseRecord);
	//	break;
	//case EMenuItem::StartGameGoBack:
	//	PlayClose(EMenuType::MainMenu);
	//	break;
	//case EMenuItem::GameOptionGoBack:
	//	PlayClose(EMenuType::MainMenu);
	//	break;
	//case EMenuItem::NewGameGoBack:
	//	PlayClose(EMenuType::StartGame);
	//	break;
	//case EMenuItem::ChooseRecordGoBack:
	//	PlayClose(EMenuType::StartGame);
	//	break;
	//case EMenuItem::EnterGame:
	//	//检测是否可以进入游戏
	//	if (NewGameWidget->AllowEnterGame())
	//	{
	//		DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SDemoMenuWidget::EnterGame);
	//	}
	//	else
	//	{
	//		//解锁按钮
	//		ControlLocked = false;
	//	}
	//	break;
	//case EMenuItem::EnterRecord:
	//	//告诉选择存档更新存档名
	//	ChooseRecordWidget->UpdateRecordName();
	//	DemoHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), MenuStyle->StartGameSound, this, &SDemoMenuWidget::EnterGame);
	//	break;
	//}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

//
//void SDemoMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
//{
//	switch (AnimState)
//	{
//	case EMenuAnim::Stop:
//		break;
//	case EMenuAnim::Close:
//		//如果正在播放
//		if (MenuAnimation.IsPlaying()) {
//			//实时修改Menu的大小
//			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, -1.f);
//			//在关闭了40%的时候设置不显示组件
//			if (MenuCurve.GetLerp() < 0.6f && IsMenuShow) ChooseWidget(EMenuType::None);
//		}
//		else {
//			//关闭动画完了,设置状态为打开
//			AnimState = EMenuAnim::Open;
//			//开始播放打开动画
//			MenuAnimation.Play(this->AsShared());
//		}
//		break;
//	case EMenuAnim::Open:
//		//如果正在播放
//		if (MenuAnimation.IsPlaying())
//		{
//			//实时修改Menu大小
//			ResetWidgetSize(MenuCurve.GetLerp() * 600.f, CurrentHeight);
//			//打开60%之后显示组件
//			if (MenuCurve.GetLerp() > 0.6f && !IsMenuShow) ChooseWidget(CurrentMenu);
//		}
//		//如果已经播放完毕
//		if (MenuAnimation.IsAtEnd())
//		{
//			//修改状态为Stop
//			AnimState = EMenuAnim::Stop;
//			//解锁按钮
//			ControlLocked = false;
//		}
//		break;
//	}
//}
//
//
//

// 修改语言
void SDemoMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	DemoDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

// 修改音量
void SDemoMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	DemoDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

//
//void SDemoMenuWidget::InitializedMenuList()
//{
//
//	//实例化主界面
//	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
//	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "StartGame", "StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GameOption", "GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	MainMenuList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "QuitGame", "QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "Menu", "Menu"), 510.f, &MainMenuList)));
//
//
//	//开始游戏界面
//	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
//	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "NewGame", "NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "LoadRecord", "LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	StartGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "StartGame", "StartGame"), 510.f, &StartGameList)));
//
//
//	//游戏设置界面
//	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
//	//实例化游戏设置的Widget
//	SAssignNew(GameOptionWidget, SDemoGameOptionWidget)
//		.ChangeCulture(this, &SDemoMenuWidget::ChangeCulture)
//		.ChangeVolume(this, &SDemoMenuWidget::ChangeVolume);
//	//添加控件到数组
//	GameOptionList.Add(GameOptionWidget);
//	GameOptionList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::GameOptionGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "GameOption", "GameOption"), 610.f, &GameOptionList)));
//
//
//	//开始新游戏界面
//	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
//	SAssignNew(NewGameWidget, SDemoNewGameWidget);
//	NewGameList.Add(NewGameWidget);
//	NewGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "EnterGame", "EnterGame")).ItemType(EMenuItem::EnterGame).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	NewGameList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::NewGameGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "NewGame", "NewGame"), 510.f, &NewGameList)));
//
//	//选择存档界面
//	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
//	SAssignNew(ChooseRecordWidget, SDemoChooseRecordWidget);
//	ChooseRecordList.Add(ChooseRecordWidget);
//	ChooseRecordList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "EnterRecord", "EnterRecord")).ItemType(EMenuItem::EnterRecord).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//	ChooseRecordList.Add(SNew(SDemoMenuItemWidget).ItemText(NSLOCTEXT("DemoMenu", "GoBack", "GoBack")).ItemType(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SDemoMenuWidget::MenuItemOnClicked));
//
//	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("DemoMenu", "LoadRecord", "LoadRecord"), 510.f, &ChooseRecordList)));
//
//
//}
//
//void SDemoMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
//{
//	//定义是否已经显示菜单
//	IsMenuShow = WidgetType != EMenuType::None;
//	//移出所有组件
//	ContentBox->ClearChildren();
//	//如果Menutype是None
//	if (WidgetType == EMenuType::None) return;
//	//循环添加组件
//	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It) {
//		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
//	}
//	//更改标题
//	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
//
//}
//
////如果不修改高度,NewHeight转入-1
//void SDemoMenuWidget::ResetWidgetSize(float NewWidget, float NewHeight)
//{
//	RootSizeBox->SetWidthOverride(NewWidget);
//	if (NewHeight < 0) return;
//	RootSizeBox->SetHeightOverride(NewHeight);
//}
//
//void SDemoMenuWidget::InitializedAnimation()
//{
//	//开始延时
//	const float StartDelay = 0.3f;
//	//持续时间
//	const float AnimDuration = 0.6f;
//	MenuAnimation = FCurveSequence();
//	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);
//	//初始设置Menu大小
//	ResetWidgetSize(600.f, 510.f);
//	//初始显示主界面
//	ChooseWidget(EMenuType::MainMenu);
//	//允许点击按钮
//	ControlLocked = false;
//	//设置动画状态为停止
//	AnimState = EMenuAnim::Stop;
//	//设置动画播放器跳到结尾,也就是1
//	MenuAnimation.JumpToEnd();
//}
//
//void SDemoMenuWidget::PlayClose(EMenuType::Type NewMenu)
//{
//	//设置新的界面
//	CurrentMenu = NewMenu;
//	//设置新高度
//	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
//	//设置播放状态是Close
//	AnimState = EMenuAnim::Close;
//	//播放反向动画
//	MenuAnimation.PlayReverse(this->AsShared());
//	//播放切换菜单音乐
//	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);
//}
//
//void SDemoMenuWidget::QuitGame()
//{
//	Cast<ADemoMenuController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
//}
//
//void SDemoMenuWidget::EnterGame()
//{
//	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
//}
