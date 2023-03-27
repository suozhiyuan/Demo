// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoPointerWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoPointerWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	//初始化大小为20
	CurrentSize = 20.f;
	// IsAimed = false;

	ChildSlot
		[
			SAssignNew(RootBox, SBox)
			.WidthOverride(TAttribute<FOptionalSize>(this, &SDemoPointerWidget::GetBoxWidget))
			.HeightOverride(TAttribute<FOptionalSize>(this, &SDemoPointerWidget::GetBoxHeight))
			[
				SNew(SImage)
				.Image(&GameStyle->PointerBrush)
			]
		];


	//加载材质实例
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Material/PointerMatInst.PointerMatInst'"));

	//转换为动态材质实例
	PointerMaterial = (UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}


void SDemoPointerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//实时修改空间大小
	CurrentSize = IsAimed ? FMath::FInterpTo(CurrentSize, 130.f, InDeltaTime, 10.f) : FMath::FInterpTo(CurrentSize, 20.f, InDeltaTime, 10.f);
}

//给PlayerController绑定的事件,修改准星是否锁定以及加载进度
void SDemoPointerWidget::UpdatePointer(bool IsAim, float Range)
{
	IsAimed = IsAim;
	PointerMaterial->SetScalarParameterValue(FName("Range"), Range);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FOptionalSize SDemoPointerWidget::GetBoxWidget() const
{
	return FOptionalSize(CurrentSize);
}

FOptionalSize SDemoPointerWidget::GetBoxHeight() const
{
	return FOptionalSize(CurrentSize);
}
