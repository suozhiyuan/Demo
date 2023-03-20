// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "DemoMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct DEMO_API FDemoMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FDemoMenuStyle();
	virtual ~FDemoMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FDemoMenuStyle& GetDefault();


	/*
	 * �˵� HUD ����ͼƬ
	 */
	UPROPERTY(EditAnywhere, Category = MenuHUD)
		FSlateBrush MenuHUDBackgroundBrush;					// FSlateBrush ��ˢ

	/*
	* ָ��Menu�ı���ͼƬ
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush MenuBackgroundBrush;

	/*
	* Menu��ͼ���Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush LeftIconBrush;

	/*
	* Menu��ͼ���Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush RightIconBrush;

	/*
	* Menu����Border��Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush TitleBorderBrush;


	/*
	* MenuItem��Brush
	*/
	UPROPERTY(EditAnywhere, Category = MenuItem)
		FSlateBrush MenuItemBrush;

	/*
	* 60������
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;

	/*
	* 40������
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	/*
	* 30������
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	/*
	* ��ɫ��ɫ
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	/*
	* ��ɫ��ɫ
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;

	/*
	* GameSet�ı���
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush GameOptionBGBrush;

	/*
	* CheckedBox �� Brush ��ѡ��
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush CheckedBoxBrush;

	/*
	* CheckedBox �� Brush ����ѡ��
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush UnCheckedBoxBrush;

	/*
	* Slider�ı���Brush
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush SliderBarBrush;

	/*
	* ָ��Slider(������)����ʽ
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSliderStyle SliderStyle;


	/*
	* ��ʼ��Ϸ����
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound StartGameSound;

	/*
	* ������Ϸ����
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound ExitGameSound;

	/*
	* ת����ť����
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound MenuItemChangeSound;

	/*
	* Menu��������
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound MenuBackgroundMusic;

};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UDemoMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FDemoMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
