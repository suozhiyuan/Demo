// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct CompoundTable;
struct ResourceAttribute;
struct ObjectAttribute;
class USoundCue;
enum class ECultureTeam : uint8;
/**
 * 
 */
class DEMO_API DemoDataHandle
{// Fill out your copyright notice in the Description page of Project Settings.

public:
	DemoDataHandle();

	static void Initialize();

	static TSharedPtr<DemoDataHandle> Get();

	//修改中英文
	void ChangeLocalizationCulture(ECultureTeam Culture);
	//修改菜单音量
	void ResetMenuVolume(float MusicVol, float SoundVol);
	//修改游戏音量
	void ResetGameVolume(float MusicVol, float SoundVol);
	//游戏数据初始化
	void InitializeGameData();
	//添加新存档名
	void AddNewRecord();

public:
	//语言
	ECultureTeam CurrentCulture;
	//音量
	float MusicVolume;
	float SoundVolume;
	//存档数据
	TArray<FString> RecordDataList;
	//存档名
	FString RecordName;
	//物品属性图
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;
	//物品贴图资源数组
	TArray<const FSlateBrush*> ObjectBrushList;
	//资源属性图
	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;
	//合成表图
	TArray<TSharedPtr<CompoundTable>> CompoundTableMap;

private:

	//创建单例
	static TSharedRef<DemoDataHandle> Create();

	//根据enum类型获取字符串
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	//根据字符串获取Enum值
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

	//初始化存档数据
	void InitRecordData();
	//初始化Menu声音数据
	void InitializedMenuAudio();
	//初始化物品属性图
	void InitObjectAttr();
	//初始化资源属性图
	void InitResourceAttrMap();
	//初始化合成表图
	void InitCompoundTableMap();
	//初始化Game声音数据
	void InitializeGameAudio();

private:
	static TSharedPtr<DemoDataHandle> DataInstance;

	//保存Menu的声音
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;

	//获取MenuStyle,里面存放有声音文件
	const struct FDemoMenuStyle* MenuStyle;

	//获取GameStyle
	const struct FDemoGameStyle* GameStyle;

	//音乐组件
	USoundMix* DemoSoundMix;
	USoundClass* DemoMusicClass;
	USoundClass* DemoSoundClass;
	FAudioDevice* AudioDevice;			// 音乐播放设备
};
