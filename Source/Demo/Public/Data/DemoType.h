// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ECultureTeam : uint8
{
	EN = 0,
	ZH
};

//Menu按钮的类型
namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,				// 开始游戏
		GameOption,				// 游戏设置
		QuitGame,				// 退出游戏
		NewGame,				// 新游戏
		LoadRecord,				// 加载存档
		StartGameGoBack,		// 开始游戏的返回
		GameOptionGoBack,		// 游戏设置的返回
		NewGameGoBack,			// 新游戏的返回
		ChooseRecordGoBack,		// 选择存档的返回
		EnterGame,				// 进入游戏
		EnterRecord				// 进入存档
	};
}

//Menu界面类型
namespace EMenuType
{
	enum Type
	{
		None,
		MainMenu,				// 主菜单
		StartGame,				// 开始游戏戏菜单
		GameOption,				// 游戏设置菜单
		NewGame,				// 新游戏菜单
		ChooseRecord			// 选择存档菜单
	};
}

//Menu动画状态枚举
namespace EMenuAnim
{
	enum Type
	{
		Stop,					// 停止动画
		Close,					// 关闭Menu
		Open					// 打开Menu
	};
}

//视角模式
namespace EGameViewMode
{
	enum Type
	{
		First,
		Third
	};
}

//上半身动画的状态
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,		// 拳击
		Hit,		// 锤子敲
		Fight,		// 挥剑
		PickUp,		// 拾取
		Eat			// 吃
	};
}

//物品类型
namespace EObjectType
{
	enum Type
	{
		Normal = 0,			//普通物品,木头,石头
		Food,				//食物,苹果,肉
		Tool,				//工具,锤子,斧子
		Weapon				//武器,剑
	};
}

//物品属性结构体
struct ObjectAttribute
{
	FText EN;						//英文名
	FText ZH;						//中文名
	EObjectType::Type ObjectType;	//物品类型
	int PlantAttack;				//对植物的攻击力
	int MetalAttcck;				//对金属资源的攻击力
	int AnimalAttack;				//对动物的攻击力
	int AffectRange;				//攻击距离
	FString TexPath;				//图片路径

	//构造函数
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA, const int AA, const int AR, const FString TP) {
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttcck = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}

	// Debug
	//FString ToString()
	//{
	//	return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ObjectType) + FString("--") + FString::FromInt(PlantAttack) + FString("--") + FString::FromInt(MetalAttcck) + FString("--") + FString::FromInt(AnimalAttack) + FString("--") + FString::FromInt(AffectRange) + FString("--") + TexPath;
	//}
};

//快捷栏容器结构体
struct ShortcutContainer
{
	int ObjectIndex;								// 物品ID
	int ObjectNum;									// 物品数量
	TSharedPtr<SBorder> ContainerBorder;			// 快捷栏的一个格子
	TSharedPtr<SBorder> ObjectImage;				// 快捷栏物品图片
	TSharedPtr<STextBlock> ObjectNumText;			// 快捷栏图标上的文字
	const FSlateBrush* NormalContainerBrush;		// 快捷栏容器图标，正常状态
	const FSlateBrush* ChoosedContainerBrush;		// 快捷栏容器图标，选中
	TArray<const FSlateBrush*>* ObjectBrushList;	

	ShortcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT, const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*>* OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;

		//初始化显示设置
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage((*ObjectBrushList)[0]);
	}

	//设置是否选中当前的物品,true就是要选中,返回物品类型
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		}
		else {
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	//设置Index
	ShortcutContainer* SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		ObjectImage->SetBorderImage((*ObjectBrushList)[ObjectIndex]);
		return this;
	}

	//设置数量
	ShortcutContainer* SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		//如果数量为0或者1,不显示数字
		if (ObjectNum == 0 || ObjectNum == 1) 
		{
			ObjectNumText->SetText(FString(""));
		}
		else 
		{
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}
		return this;
	}
};

//资源类型
namespace EResourceType
{
	enum Type
	{
		Plant = 0,
		Metal,
		Animal
	};
}

//资源属性结构体
struct ResourceAttribute
{
	FText EN;//英文名
	FText ZH;//中文名
	EResourceType::Type ResourceType;
	int HP;
	TArray<TArray<int>> FlobObjectInfo;

	ResourceAttribute(const FText ENName, const FText ZHName, const EResourceType::Type RT, const int HPValue, TArray<TArray<int>>* FOI)
	{
		EN = ENName;
		ZH = ZHName;
		ResourceType = RT;
		HP = HPValue;

		//将数组元素迭代进本地数组
		for (TArray<TArray<int>>::TIterator It(*FOI); It; ++It) 
		{
			TArray<int> FlobObjectInfoItem;
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) 
			{
				FlobObjectInfoItem.Add(*Ih);
			}
			FlobObjectInfo.Add(FlobObjectInfoItem);
		}
	}

	//// 测试代码
	//FString ToString()
	//{
	//	FString InfoStr;
	//	for (TArray<TArray<int>>::TIterator It(FlobObjectInfo); It; ++It) 
	//	{
	//		for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) 
	//		{
	//			InfoStr += FString::FromInt(*Ih) + FString(".");
	//		}
	//		InfoStr += FString("__");
	//	}
	//	return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ResourceType) + FString("--") + FString::FromInt(HP) + FString("--") + InfoStr;
	//}
};

// Game界面分类
namespace EGameUIType
{
	enum Type
	{
		Game,//游戏模式UI
		Pause,//暂停
		Lose,//输了,死亡
		Package,//背包
		ChatRoom//聊天室
	};
}

//背包容器类型
namespace EContainerType
{
	enum Type
	{
		Output,//合成表输出
		Input,//合成表输入
		Normal,//普通容器
		Shortcut,//快捷栏容器
	};
}

//合成表结构体
struct CompoundTable
{
	//合成图
	TArray<int> CompoundMap;

	//构造函数
	CompoundTable(TArray<int>* InsertMap)
	{
		for (TArray<int>::TIterator It(*InsertMap); It; ++It) 
		{
			CompoundMap.Add(*It);
		}
	}

	/**
	 * @brief 检测符合表的输出物品ID和数量
	 * @param IDMap			传入物体的ID
	 * @param NumMap		传入物体的数量
	 * @param OutputID		输出物体的ID
	 * @param OutputNum		输出物体的数量
	 */
	void DetectTable(TArray<int>* IDMap, TArray<int>* NumMap, int& OutputID, int& OutputNum)
	{
		//先默认设定输出ID为表输出ID
		int TempID = CompoundMap[9];

		//先设定输出数量为64,一点一点减去
		int TempNum = 64;

		for (int i = 0; i < 9; ++i)
		{
			if ((*IDMap)[i] == CompoundMap[i])	// 合成表第一个内容 是否与合成容器的相等
			{
				if ((*IDMap)[i] != 0) TempNum = (*NumMap)[i] < TempNum ? (*NumMap)[i] : TempNum;		// 然后判断合成容器中物品的数量，大于64则最大64
			}
			else
			{
				TempID = TempNum = 0;
				break;
			}
		}

		//如果输出ID不为空则说明有匹配数据，更新Output数据
		if (TempID != 0 && TempNum != 0) 
		{
			OutputID = TempID;
			OutputNum = TempNum;
		}
	}
	
	/**
	 * @brief 根据输入的物品 和 输出物品序列 以及 生产数量，查询出是否匹配这个合成表，并且输出消耗数组
	 * @param TableMap 合成栏物品ID
	 * @param ProductNum 合成结果数量（拿出的）
	 * @param ExpendMap 合成栏物品对应减少的数量
	 * @return 返回是否匹配
	 */
	bool DetectExpend(TArray<int>* TableMap, int ProductNum, TArray<int>& ExpendMap)
	{
		//是否匹配这个合成表,开始设置为true
		bool IsMatch = true;

		for (int i = 0; i < 10; ++i) 
		{
			// 合成栏内容与配置文件对比，只要有一个不符合,直接设置false
			if ((*TableMap)[i] != CompoundMap[i])
			{
				IsMatch = false;
				break;
			}
		}

		//如果匹配
		if (IsMatch) 
		{
			for (int i = 0; i < 9; ++i) 
			{
				//如果不为0,直接Add生产的数量
				if (CompoundMap[i] != 0) 
				{
					ExpendMap.Add(ProductNum);
				}
				else 
				{
					ExpendMap.Add(0);
				}
			}
		}
		//返回是否匹配
		return IsMatch;
	}
};

//敌人AI状态
UENUM(BlueprintType)
enum  class EEnemyAIState : uint8
{
	ES_Patrol    UMETA(DisplayName = "Patrol"),
	ES_Chase     UMETA(DisplayName = "Chase"),
	ES_Escape    UMETA(DisplayName = "Escape"),
	ES_Attack    UMETA(DisplayName = "Attack"),
	ES_Hurt      UMETA(DisplayName = "Hurt"),
	ES_Defence   UMETA(DisplayName = "Defence"),
	ES_Dead      UMETA(DisplayName = "Dead")
};

//敌人攻击状态
UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	EA_Normal   UMETA(DisplayName = "Normal"),
	EA_Dash     UMETA(DisplayName = "Dash"),
	EA_Pursuit  UMETA(DisplayName = "Pursuit")
};

//小地图缩放状态
namespace EMiniMapSizeMode
{
	enum Type
	{
		None,
		Add,
		Reduce
	};
}