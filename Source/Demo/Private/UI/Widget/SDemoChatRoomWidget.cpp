// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoChatRoomWidget.h"
#include "SlateOptMacros.h"


//
//struct ChatMessItem
//{
//	//水平组件
//	TSharedPtr<SHorizontalBox> CSBox;
//	//名字
//	TSharedPtr<STextBlock> CSName;
//	//内容框
//	TSharedPtr<SBorder> CSBorder;
//	//内容
//	TSharedPtr<SMultiLineEditableText> CSContent;
//	//构造
//	ChatMessItem(const FSlateBrush* EmptyBrush, const FSlateFontInfo FontInfo)
//	{
//		//实例化组件
//		SAssignNew(CSBox, SHorizontalBox)
//
//			+ SHorizontalBox::Slot()
//			.HAlign(HAlign_Fill)
//			.VAlign(VAlign_Fill)
//			.AutoWidth()
//			[
//				SAssignNew(CSName, STextBlock)
//				.Font(FontInfo)
//			.ColorAndOpacity(TAttribute<FSlateColor>(FSlateColor(FLinearColor(0.f, 1.f, 0.f, 1.f))))
//			]
//
//		+ SHorizontalBox::Slot()
//			.HAlign(HAlign_Fill)
//			.VAlign(VAlign_Fill)
//			.FillWidth(1.f)
//			[
//				SAssignNew(CSBorder, SBorder)
//				.BorderImage(EmptyBrush)
//			.HAlign(HAlign_Fill)
//			.VAlign(VAlign_Fill)
//			[
//				SAssignNew(CSContent, SMultiLineEditableText)
//				.WrappingPolicy(ETextWrappingPolicy::AllowPerCharacterWrapping)
//			.AutoWrapText(true)
//			.Font(FontInfo)
//			]
//			];
//	}
//
//	//激活组件
//	TSharedPtr<SHorizontalBox> ActiveItem(FText NewName, FText NewContent) {
//		CSName->SetText(NewName);
//		CSContent->SetText(NewContent);
//		return CSBox;
//	}
//};
//


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDemoChatRoomWidget::Construct(const FArguments& InArgs)
{

	////获取GameStyle
	//GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	//ChildSlot
	//	[

	//		SNew(SBox)
	//		.WidthOverride(600.f)
	//	.HeightOverride(1080.f)
	//	[
	//		SNew(SBorder)
	//		.BorderImage(&GameStyle->ChatRoomBGBrush)
	//	[
	//		SNew(SOverlay)

	//		+ SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Bottom)
	//	.Padding(FMargin(0.f, 0.f, 0.f, 80.f))
	//	[
	//		SAssignNew(ScrollBox, SScrollBox)
	//	]

	//+ SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Fill)
	//	.Padding(FMargin(0.f, 1000.f, 0.f, 0.f))
	//	[

	//		SNew(SOverlay)

	//		+ SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Fill)
	//	.Padding(FMargin(0.f, 0.f, 120.f, 0.f))
	//	[
	//		SAssignNew(EditTextBox, SEditableTextBox)
	//		.Font(GameStyle->Font_30)
	//	.OnTextCommitted(this, &SDemoChatRoomWidget::SubmitEvent)
	//	]

	//+ SOverlay::Slot()
	//	.HAlign(HAlign_Fill)
	//	.VAlign(VAlign_Fill)
	//	.Padding(FMargin(480.f, 0.f, 0.f, 0.f))
	//	[
	//		SNew(SButton)
	//		.HAlign(HAlign_Center)
	//	.VAlign(VAlign_Center)
	//	.OnClicked(this, &SDemoChatRoomWidget::SendEvent)
	//	[
	//		SNew(STextBlock)
	//		.Font(GameStyle->Font_30)
	//	.Text(NSLOCTEXT("DemoGame", "Send", "Send"))
	//	]

	//	]


	//	]

	//	]

	//	]

	//	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
//
//void SDemoChatRoomWidget::SubmitEvent(const FText& SubmitText, ETextCommit::Type CommitType)
//{
//	FString MessageStr = EditTextBox->GetText().ToString();
//	if (MessageStr.IsEmpty()) return;
//	MessageStr = FString(": ") + MessageStr;
//	AddMessage(NSLOCTEXT("DemoGame", "Player", "Player"), FText::FromString(MessageStr));
//	EditTextBox->SetText(FText::FromString(""));
//	PushMessage.ExecuteIfBound(NSLOCTEXT("DemoGame", "Player", "Player"), FText::FromString(MessageStr));
//}
//
//FReply SDemoChatRoomWidget::SendEvent()
//{
//	FString MessageStr = EditTextBox->GetText().ToString();
//	if (MessageStr.IsEmpty()) return FReply::Handled();
//	MessageStr = FString(": ") + MessageStr;
//	AddMessage(NSLOCTEXT("DemoGame", "Player", "Player"), FText::FromString(MessageStr));
//	EditTextBox->SetText(FText::FromString(""));
//	PushMessage.ExecuteIfBound(NSLOCTEXT("DemoGame", "Player", "Player"), FText::FromString(MessageStr));
//	return FReply::Handled();
//}
//
//void SDemoChatRoomWidget::AddMessage(FText NewName, FText NewContent)
//{
//	TSharedPtr<ChatMessItem> InsertItem;
//
//	if (MessageList.Num() < 30)
//	{
//		//新建一个控件
//		InsertItem = MakeShareable(new ChatMessItem(&GameStyle->EmptyBrush, GameStyle->Font_30));
//		MessageList.Add(InsertItem);
//		ScrollBox->AddSlot()
//			[
//				InsertItem->ActiveItem(NewName, NewContent)->AsShared()
//			];
//	}
//	else
//	{
//		//从序列里面提取
//		InsertItem = MessageList[0];
//		//出队列
//		MessageList.Remove(InsertItem);
//		ScrollBox->RemoveSlot(InsertItem->CSBox->AsShared());
//		//入队列
//		ScrollBox->AddSlot()
//			[
//				InsertItem->ActiveItem(NewName, NewContent)->AsShared()
//			];
//		MessageList.Push(InsertItem);
//	}
//	//设置滑动到最底下
//	ScrollBox->ScrollToEnd();
//}
//
//void SDemoChatRoomWidget::ScrollToEnd()
//{
//	ScrollBox->ScrollToEnd();
//}
