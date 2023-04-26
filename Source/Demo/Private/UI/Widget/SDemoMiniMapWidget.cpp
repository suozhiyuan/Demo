// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SDemoMiniMapWidget.h"
#include "SlateOptMacros.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UI/Style/DemoGameWidgetStyle.h"
#include "UI/Style/DemoStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDemoMiniMapWidget::Construct(const FArguments& InArgs)
{
	//��ȡGameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");


	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(320.f)
			.HeightOverride(320.f)
			[
				SNew(SOverlay)

				//MiniMap����ͼƬ
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->MiniMapBGBrush)
				]

				//��ȾMiniMap��ͼƬ
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SAssignNew(MiniMapImage, SImage)
				]

				//��Ⱦ�����Ұ��ͼƬ
				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SAssignNew(EnemyViewImage, SImage)
					]
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION



void SDemoMiniMapWidget::RegisterMiniMap(UTextureRenderTarget2D* MiniMapRender)
{
	//��ȡ���ʣ�������������֣�һ��Բ�ε�����
	UMaterialInterface* MiniMapMatInst = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/MiniMapMatInst.MiniMapMatInst'"));

	//�������ֶ�̬���ʣ� ������񴫹�����ͼ��
	UMaterialInstanceDynamic* MiniMapMatDynamic = UMaterialInstanceDynamic::Create(MiniMapMatInst, nullptr);

	//�󶨲�������
	//MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"), Cast<UTexture>(MiniMapRender));
	MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"), MiniMapRender);

	//ʵ����MiniMap��ˢ
	MiniMapBrush = new FSlateBrush();

	//��������
	MiniMapBrush->ImageSize = FVector2D(280.f, 280.f);	// ���ƴ�С
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;			// ��������

	//�󶨲�����Դ�ļ�
	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);

	//����ˢ��ΪMiniMapImage�ı�ˢ
	MiniMapImage->SetImage(MiniMapBrush);

	//������Ұ�����趨
	UMaterialInterface* EnemyViewMatInst = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/EnemyViewMatInst.EnemyViewMatInst'"));

	//����������Ұ�Ķ�̬����
	EnemyViewMatDynamic = UMaterialInstanceDynamic::Create(EnemyViewMatInst, nullptr);

	//ʵ����EnemyView��ˢ
	FSlateBrush* EnemyViewBrush = new FSlateBrush();

	//��������
	EnemyViewBrush->ImageSize = FVector2D(280.f, 280.f);
	EnemyViewBrush->DrawAs = ESlateBrushDrawType::Image;

	//�󶨲�����Դ�ļ�
	EnemyViewBrush->SetResourceObject(EnemyViewMatDynamic);

	//����ˢ��ΪMiniMapImage�ı�ˢ
	EnemyViewImage->SetImage(EnemyViewBrush);

	//��ɫΪ͸����
	EnemyViewImage->SetColorAndOpacity(FLinearColor(0.3f, 1.f, 0.32f, 0.4f));
}

void SDemoMiniMapWidget::UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList)
{
	//��ȡYaw,���Yaw��180��-180,���ǰ�����ɸ���,Ȼ��ͨ���ӽǶ�������
	float YawDir = -PlayerRotator.Yaw;

	//ʹ�����Ǻ��������㵥λ����,��150�İ뾶��160�����ĵ㣬DegreesToRadians ��ŷ���Ƕ�ת��Ϊ����
	NorthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir)), FMath::Cos(FMath::DegreesToRadians(YawDir))) * 150.f + FVector2D(160.f, 160.f);
	EastLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 90.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 90.f))) * 150.f + FVector2D(160.f, 160.f);
	SouthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 180.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 180.f))) * 150.f + FVector2D(160.f, 160.f);
	WestLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 270.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 270.f))) * 150.f + FVector2D(160.f, 160.f);

	// ��ͼ�ߴ�
	MapSize = MiniMapSize;
	// ������ڵĵ����б�
	EnemyPos.Empty();
	// ��յ����Ƿ������б�
	EnemyLock.Empty();
	// ���ű���
	float DPIRatio = 280.f / MapSize;

	// ������Ұ��ת��Ϣ
	TArray<float> EnemyViewRotate;
	// ������Ұλ����Ϣ
	TArray<FVector2D> EnemyViewPos;
	// ������Ұ������Ϣ
	TArray<bool> EnemyViewLock;

	//��ȡ������Ϣ
	for (int i = 0; i < (*EnemyPosList).Num(); ++i)
	{
		//����ʵ�ʳ���
		float RealDistance = (*EnemyPosList)[i].Size();			// Size ��ȡ�����ĳ���
		//�������С�ڵ�ͼʵ�ʰ뾶���㽫����ͼ����ʾ����
		if (RealDistance * 2 < MapSize)
		{
			//�����ͼUI�е�λ��
			EnemyPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));
			//�Ƿ��������
			EnemyLock.Add((*EnemyLockList)[i]);
		}
		//�������С��С��ͼʵ�ʰ뾶�ټ���2000,����Ⱦ��Ұ
		if (RealDistance * 2 < MapSize + 2000.f)
		{
			//�����ͼUI�е�λ��
			EnemyViewPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));
			//�Ƿ��������
			EnemyViewLock.Add((*EnemyLockList)[i]);
			//������ת��Ϣ,��ʽ��Ϊ0-1
			float RotVal = -(*EnemyRotateList)[i];
			if (RotVal > 180.f) RotVal -= 360.f;
			if (RotVal < -180.f) RotVal += 360.f;
			//���л���0-360
			RotVal += 180.f;
			//���л�0-1
			RotVal /= 360.f;
			//ת��180��
			RotVal = RotVal + 0.5f > 1.f ? RotVal - 0.5f : RotVal + 0.5f;
			EnemyViewRotate.Add(RotVal);
		}
	}

	int ViewCount = 0;

	//�޸ĵ�����Ұ���ű���
	EnemyViewMatDynamic->SetScalarParameterValue(FName("Scale"), 1000.f / MapSize);
	for (int i = 0; i < EnemyViewPos.Num(); ++i, ++ViewCount) 
	{
		FString PosName = FString("Position_") + FString::FromInt(i + 1);
		FString AngleName = FString("Angle_") + FString::FromInt(i + 1);

		//���û������Ҿ���Ⱦ
		if (!EnemyViewLock[i]) 
		{
			EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor((EnemyViewPos[i].X - 20.f) / 280.f, (EnemyViewPos[i].Y - 20.f) / 280.f, 0.f, 0.f));
			EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), EnemyViewRotate[i]);
		}
		else
		{
			EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor(0.f, 0.f, 0.f, 0.f));
			EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), 0.f);
		}
	}

	//��ʣ�µ���Ұ������Ⱦ
	for (ViewCount += 1; ViewCount < 11; ++ViewCount) 
	{
		FString PosName = FString("Position_") + FString::FromInt(ViewCount);
		FString AngleName = FString("Angle_") + FString::FromInt(ViewCount);
		EnemyViewMatDynamic->SetVectorParameterValue(FName(*PosName), FLinearColor(0.f, 0.f, 0.f, 0.f));
		EnemyViewMatDynamic->SetScalarParameterValue(FName(*AngleName), 0.f);
	}
}

int32 SDemoMiniMapWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//�ȵ���һ�¸��ຯ��
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	//��Ⱦ���ͼ�꣬ MakeBox ����ͼƬ
	FSlateDrawElement::MakeBox
	(
		OutDrawElements,				//
		LayerId + 10,					// ����Խ�󣬲㼶Խ��
		AllottedGeometry.ToPaintGeometry(FVector2D(155.f, 155.f), FVector2D(10.f, 10.f)),		// λ���Լ���С
		&GameStyle->PawnPointBrush,		// ��ˢ
		ESlateDrawEffect::None,			// Ч��
		FLinearColor(1.f, 1.f, 0.f, 1.f)		// ��ɫ
	);

	//��Ⱦ�����ϱ����֣� MakeText ��������
	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(NorthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("DemoGame", "N", "N"),
		GameStyle->Font_20,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(SouthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("DemoGame", "S", "S"),
		GameStyle->Font_20,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(EastLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("DemoGame", "E", "E"),
		GameStyle->Font_20,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);
	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId + 10,
		AllottedGeometry.ToPaintGeometry(WestLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
		NSLOCTEXT("DemoGame", "W", "W"),
		GameStyle->Font_20,
		ESlateDrawEffect::None,
		FLinearColor(1.f, 1.f, 1.f, 1.f)
	);

	//��Ⱦ����λ�ã���ɫΪ������ң���ɫΪû������
	for (int i = 0; i < EnemyPos.Num(); ++i) 
	{
		//��Ⱦ���ͼ��
		FSlateDrawElement::MakeBox
		(
			OutDrawElements,
			LayerId + 10,
			AllottedGeometry.ToPaintGeometry(EnemyPos[i] - FVector2D(5.f, 5.f), FVector2D(10.f, 10.f)),
			&GameStyle->PawnPointBrush,
			ESlateDrawEffect::None,
			EnemyLock[i] ? FLinearColor(1.f, 0.f, 0.f, 1.f) : FLinearColor(0.f, 1.f, 0.f, 1.f)
		);
	}

	return LayerId;
}