// 这个类的作用是，获取组件样式，以及把风格注册进游戏

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class DEMO_API DemoStyle
{
public:
	static void Initialze();

	static FName GetStyleSetName();			// 获取样式名字，这个名字是注册进游戏中的名字

	static void ShutDown();					// 游戏关闭时调用，取消注册

	static const ISlateStyle& Get();		// 给外部调用，获取这个单例

private:

	static TSharedRef<class FSlateStyleSet> Create();		//FSlateStyleSet类模板，一个包含外观的属性集合,用来注册样式
	static TSharedPtr<FSlateStyleSet> DemoStyleInstance;	//作为单例模式，这个变量一定不能放到构造函数里去实现

};
