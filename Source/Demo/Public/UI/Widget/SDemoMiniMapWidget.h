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

	//��д���ƺ���
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	//ί�н���GameMode��������Texture��Դ
	void RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender);
	
	/**
	 * @brief ί�н���GameMode�������������ת,�󶨵�ί����GameMode��UpdateMapDirection
	 * @param PlayerRotator			��ҵ���ת
	 * @param MiniMapSize			С��ͼ�Ĵ�С
	 * @param EnemyPosList			���˵�λ�� 2D
	 * @param EnemyLockList			�����Ƿ��Ѿ����������
	 * @param EnemyRotateList		���˵���ת
	 */
	void UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize, const TArray<FVector2D>* EnemyPosList, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList);

private:
	//��ȡGameStyle
	const struct FDemoGameStyle* GameStyle;

	//��ʾMiniMap��ͼƬ
	TSharedPtr<SImage> MiniMapImage;

//	//��ʾ�����Ұ��ͼƬ
//	TSharedPtr<SImage> EnemyViewImage;

	//��Ұ����
	class UMaterialInstanceDynamic* EnemyViewMatDynamic;

	//MiniMap��ˢ
	struct FSlateBrush* MiniMapBrush;

	//�ĸ��������Ⱦλ��
	FVector2D NorthLocation;		// ����λ��
	FVector2D SouthLocation;		// �ϵ�λ��
	FVector2D EastLocation;			// ����λ��
	FVector2D WestLocation;			// ����λ��

	//С��ͼ�ߴ�
	float MapSize;

	//�����������ҵ�λ��
	TArray<FVector2D> EnemyPos;

	//�����Ƿ����������
	TArray<bool> EnemyLock;
};
