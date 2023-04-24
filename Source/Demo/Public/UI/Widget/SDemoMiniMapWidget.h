// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class DEMO_API SDemoMiniMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDemoMiniMapWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//重写绘制函数
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	//委托接受GameMode传过来的Texture资源
	void RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender);
	
	/**
	 * @brief 委托接受GameMode传过来的玩家旋转,绑定的委托是GameMode的UpdateMapDirection
	 * @param PlayerRotator			玩家的旋转
	 * @param MiniMapSize			小地图的大小
	 * @param EnemyPosList			敌人的位置 2D
	 * @param EnemyLockList			敌人是否已经锁定了玩家
	 * @param EnemyRotateList		敌人的旋转
	 */
	void UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList);

private:
	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	//显示MiniMap的图片
	TSharedPtr<SImage> MiniMapImage;

//	//显示玩家视野的图片
//	TSharedPtr<SImage> EnemyViewImage;

	//视野材质
	class UMaterialInstanceDynamic* EnemyViewMatDynamic;

	//MiniMap笔刷
	struct FSlateBrush* MiniMapBrush;

	//四个方向的渲染位置
	FVector2D NorthLocation;		// 北的位置
	FVector2D SouthLocation;		// 南的位置
	FVector2D EastLocation;			// 东的位置
	FVector2D WestLocation;			// 西的位置

	//小地图尺寸
	float MapSize;

	//敌人相对于玩家的位置
	TArray<FVector2D> EnemyPos;

	//敌人是否锁定了玩家
	TArray<bool> EnemyLock;
};
