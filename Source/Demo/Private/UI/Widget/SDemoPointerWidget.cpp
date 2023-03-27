// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoPointerWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoPointerWidget::Construct(const FArguments& InArgs)
{
	//��ȡGameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	//��ʼ����СΪ20
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


	//���ز���ʵ��
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Material/PointerMatInst.PointerMatInst'"));

	//ת��Ϊ��̬����ʵ��
	PointerMaterial = (UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}


void SDemoPointerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//ʵʱ�޸Ŀռ��С
	CurrentSize = IsAimed ? FMath::FInterpTo(CurrentSize, 130.f, InDeltaTime, 10.f) : FMath::FInterpTo(CurrentSize, 20.f, InDeltaTime, 10.f);
}

//��PlayerController�󶨵��¼�,�޸�׼���Ƿ������Լ����ؽ���
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
