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
	 * 菜单 HUD 背景图片
	 */
	UPROPERTY(EditAnywhere, Category = MenuHUD)
		FSlateBrush MenuHUDBackgroundBrush;					// FSlateBrush 笔刷

	/*
	* 指定Menu的背景图片
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush MenuBackgroundBrush;

	/*
	* Menu左图标的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush LeftIconBrush;

	/*
	* Menu右图标的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush RightIconBrush;

	/*
	* Menu标题Border的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush TitleBorderBrush;


	/*
	* MenuItem的Brush
	*/
	UPROPERTY(EditAnywhere, Category = MenuItem)
		FSlateBrush MenuItemBrush;

	/*
	* 60号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;

	/*
	* 40号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	/*
	* 30号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	/*
	* 黑色颜色
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	/*
	* 白色颜色
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;

	/*
	* GameSet的背景
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush GameOptionBGBrush;

	/*
	* CheckedBox 的 Brush 被选中
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush CheckedBoxBrush;

	/*
	* CheckedBox 的 Brush 不被选中
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush UnCheckedBoxBrush;

	/*
	* Slider的背景Brush
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSlateBrush SliderBarBrush;

	/*
	* 指定Slider(滑动条)的样式
	*/
	UPROPERTY(EditAnywhere, Category = GameOption)
		FSliderStyle SliderStyle;


	/*
	* 开始游戏声音
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound StartGameSound;

	/*
	* 结束游戏声音
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound ExitGameSound;

	/*
	* 转换按钮声音
	*/
	UPROPERTY(EditAnywhere, Category = Sound)
		FSlateSound MenuItemChangeSound;

	/*
	* Menu背景声音
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
