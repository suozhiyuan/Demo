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
	//获取GameStyle
	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");

	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(320.f)
			.HeightOverride(320.f)
			[
				SNew(SOverlay)

				//MiniMap背景图片
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->MiniMapBGBrush)
				]

				//渲染MiniMap的图片
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SAssignNew(MiniMapImage, SImage)
				]

				//渲染玩家视野的图片
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
	//获取材质，这个材质是遮罩，一个圆形的遮罩
	UMaterialInterface* MiniMapMatInst = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/MiniMapMatInst.MiniMapMatInst'"));

	//创建遮罩动态材质， 存放摄像传过来的图像
	UMaterialInstanceDynamic* MiniMapMatDynamic = UMaterialInstanceDynamic::Create(MiniMapMatInst, nullptr);

	//绑定材质属性
	MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"), MiniMapRender);

	//实例化MiniMap笔刷
	MiniMapBrush = new FSlateBrush();

	//设置属性
	MiniMapBrush->ImageSize = FVector2D(280.f, 280.f);	// 绘制大小
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;			// 绘制类型

	//绑定材质资源文件
	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);

	//将笔刷作为MiniMapImage的笔刷
	MiniMapImage->SetImage(MiniMapBrush);

	//敌人视野材质设定
	UMaterialInterface* EnemyViewMatInst = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/EnemyViewMatInst.EnemyViewMatInst'"));

	//创建敌人视野材动态材质
	EnemyViewMatDynamic = UMaterialInstanceDynamic::Create(EnemyViewMatInst, nullptr);

	//实例化EnemyView笔刷
	FSlateBrush* EnemyViewBrush = new FSlateBrush();

	//设置属性
	EnemyViewBrush->ImageSize = FVector2D(280.f, 280.f);
	EnemyViewBrush->DrawAs = ESlateBrushDrawType::Image;

	//绑定材质资源文件
	EnemyViewBrush->SetResourceObject(EnemyViewMatDynamic);

	//将笔刷作为MiniMapImage的笔刷
	EnemyViewImage->SetImage(EnemyViewBrush);

	//颜色为透明绿
	EnemyViewImage->SetColorAndOpacity(FLinearColor(0.3f, 1.f, 0.32f, 0.4f));
}

void SDemoMiniMapWidget::UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList)
{
	//获取Yaw,这个Yaw从180到-180,我们把他变成负的,然后通过加角度来计算
	float YawDir = -PlayerRotator.Yaw;

	////使用三角函数来计算单位向量,加150的半径，160的中心点，DegreesToRadians 将欧拉角度转换为弧度
	NorthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir)), FMath::Cos(FMath::DegreesToRadians(YawDir))) * 150.f + FVector2D(160.f, 160.f);
	EastLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 90.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 90.f))) * 150.f + FVector2D(160.f, 160.f);
	SouthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 180.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 180.f))) * 150.f + FVector2D(160.f, 160.f);
	WestLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir + 270.f)), FMath::Cos(FMath::DegreesToRadians(YawDir + 270.f))) * 150.f + FVector2D(160.f, 160.f);

	// 地图尺寸
	MapSize = MiniMapSize;
	// 清空现在的敌人列表
	EnemyPos.Empty();
	// 清空敌人是否锁定列表
	EnemyLock.Empty();
	// 缩放比例
	float DPIRatio = 280.f / MapSize;

	// 保存视野旋转信息
	TArray<float> EnemyViewRotate;
	// 保存视野位置信息
	TArray<FVector2D> EnemyViewPos;
	// 保存视野锁定信息
	TArray<bool> EnemyViewLock;

	//获取敌人信息
	for (int i = 0; i < (*EnemyPosList).Num(); ++i)
	{
		//计算实际长度
		float RealDistance = (*EnemyPosList)[i].Size();			// Size 获取向量的长度
		//如果长度小于地图实际半径，便将敌人图标显示出来
		if (RealDistance * 2 < MapSize)
		{
			//计算地图UI中的位置
			EnemyPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));
			//是否锁定玩家
			EnemyLock.Add((*EnemyLockList)[i]);
		}
		//如果长度小于小地图实际半径再加上2000,就渲染视野
		if (RealDistance * 2 < MapSize + 2000.f)
		{
			//计算地图UI中的位置
			EnemyViewPos.Add((*EnemyPosList)[i] * DPIRatio + FVector2D(160.f, 160.f));
			//是否锁定玩家
			EnemyViewLock.Add((*EnemyLockList)[i]);
			//添加旋转信息,格式化为0-1
			float RotVal = -(*EnemyRotateList)[i];
			if (RotVal > 180.f) RotVal -= 360.f;
			if (RotVal < -180.f) RotVal += 360.f;
			//序列化到0-360
			RotVal += 180.f;
			//序列化0-1
			RotVal /= 360.f;
			//转个180度
			RotVal = RotVal + 0.5f > 1.f ? RotVal - 0.5f : RotVal + 0.5f;
			EnemyViewRotate.Add(RotVal);
		}
	}

	int ViewCount = 0;

	//修改敌人视野缩放比例
	EnemyViewMatDynamic->SetScalarParameterValue(FName("Scale"), 1000.f / MapSize);
	for (int i = 0; i < EnemyViewPos.Num(); i++)
	{
		ViewCount++;
		FString PosName = FString("Position_") + FString::FromInt(i + 1);		// 位置
		FString AngleName = FString("Angle_") + FString::FromInt(i + 1);			// 旋转

		//如果没锁定玩家就渲染
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

	//把剩下的视野都不渲染
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
	//先调用一下父类函数
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	////渲染玩家图标， MakeBox 绘制图片
	//FSlateDrawElement::MakeBox
	//(
	//	OutDrawElements,
	//	LayerId + 100,					// 数字越大，层级越上
	//	AllottedGeometry.ToPaintGeometry(FVector2D(155.f, 155.f), FVector2D(10.f, 10.f)),		// 位置以及大小
	//	&GameStyle->PawnPointBrush,		// 笔刷
	//	ESlateDrawEffect::None,			// 效果
	//	FLinearColor(1.f, 1.f, 0.f, 1.f)		// 颜色
	//);

	////渲染东西南北文字， MakeText 绘制文字
	//FSlateDrawElement::MakeText
	//(
	//	OutDrawElements,
	//	LayerId + 100,
	//	AllottedGeometry.ToPaintGeometry(NorthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
	//	NSLOCTEXT("DemoGame", "N", "N"),
	//	GameStyle->Font_20,
	//	ESlateDrawEffect::None,
	//	FLinearColor(1.f, 1.f, 1.f, 1.f)
	//);
	//FSlateDrawElement::MakeText
	//(
	//	OutDrawElements,
	//	LayerId + 100,
	//	AllottedGeometry.ToPaintGeometry(SouthLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
	//	NSLOCTEXT("DemoGame", "S", "S"),
	//	GameStyle->Font_20,
	//	ESlateDrawEffect::None,
	//	FLinearColor(1.f, 1.f, 1.f, 1.f)
	//);
	//FSlateDrawElement::MakeText
	//(
	//	OutDrawElements,
	//	LayerId + 100,
	//	AllottedGeometry.ToPaintGeometry(EastLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
	//	NSLOCTEXT("DemoGame", "E", "E"),
	//	GameStyle->Font_20,
	//	ESlateDrawEffect::None,
	//	FLinearColor(1.f, 1.f, 1.f, 1.f)
	//);
	//FSlateDrawElement::MakeText
	//(
	//	OutDrawElements,
	//	LayerId + 100,
	//	AllottedGeometry.ToPaintGeometry(WestLocation - FVector2D(8.f, 8.f), FVector2D(16.f, 16.f)),
	//	NSLOCTEXT("DemoGame", "W", "W"),
	//	GameStyle->Font_20,
	//	ESlateDrawEffect::None,
	//	FLinearColor(1.f, 1.f, 1.f, 1.f)
	//);

	////渲染敌人位置，红色为锁定玩家，绿色为没有锁定
	//for (int i = 0; i < EnemyPos.Num(); ++i) 
	//{
	//	//渲染敌人图标
	//	FSlateDrawElement::MakeBox
	//	(
	//		OutDrawElements,
	//		LayerId + 100,
	//		AllottedGeometry.ToPaintGeometry(EnemyPos[i] - FVector2D(5.f, 5.f), FVector2D(10.f, 10.f)),
	//		&GameStyle->PawnPointBrush,
	//		ESlateDrawEffect::None,
	//		EnemyLock[i] ? FLinearColor(1.f, 0.f, 0.f, 1.f) : FLinearColor(0.f, 1.f, 0.f, 1.f)
	//	);
	//}
	return LayerId;
}
