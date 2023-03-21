// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DemoDataHandle.h"

#include "Common/DemoHelper.h"
#include "Data/DemoSingleton.h"
#include "Internationalization/Internationalization.h"
#include "Data/DemoType.h"
#include "Data/DomeJsonHandle.h"


TSharedPtr<DemoDataHandle> DemoDataHandle::DataInstance = NULL;

DemoDataHandle::DemoDataHandle()
{
	//初始化存档数据
	InitRecordData();

	//初始化音乐数据
	//InitializedMenuAudio();

}

void DemoDataHandle::Initialize()
{
	if (!DataInstance.IsValid()) 
	{
		DataInstance = Create();
	}
}

TSharedPtr<DemoDataHandle> DemoDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

// 修改中英文
void DemoDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	}
	//赋值
	CurrentCulture = Culture;

	//更新存档数据
	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

TSharedRef<DemoDataHandle> DemoDataHandle::Create()
{
	TSharedRef<DemoDataHandle> DataRef = MakeShareable(new DemoDataHandle());	// MakeShareable 可以创建共享指针与共享引用
	return DataRef;
}

// 修改菜单音量
void DemoDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		////循环设置背景音量
		//for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		//{
		//	//设置音量
		//	(*It)->VolumeMultiplier = MusicVolume;
		//}
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		//{
		//	//指针的指针
		//	(*It)->VolumeMultiplier = SoundVolume;
		//}
	}
	
	//更新存档数据
	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

//void DemoDataHandle::ResetGameVolume(float MusicVol, float SoundVol)
//{
//	if (MusicVol > 0)
//	{
//		MusicVolume = MusicVol;
//		//使用混音器来设置
//		AudioDevice->SetSoundMixClassOverride(DemoSoundMix, DemoMusicClass, MusicVolume, 1.f, 0.2f, false);
//	}
//	if (SoundVol > 0)
//	{
//		SoundVolume = SoundVol;
//		//使用混音器来设置
//		AudioDevice->SetSoundMixClassOverride(DemoSoundMix, DemoSoundClass, SoundVolume, 1.f, 0.2f, false);
//	}
//	//更新存档数据
//	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
//}


// 根据enum类型获取字符串
template<typename TEnum>
FString DemoDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);		// 可通过 FindObject 从 ANY_PACKAGE 里查找 Name
	if (!EnumPtr) 
	{
		return FString("InValid");
	}
	//return EnumPtr->GetEnumName((int32)Value);			// GetEnumName 已弃用
	return EnumPtr->GetNameStringByIndex((int32)Value);
}

// 根据字符串获取Enum值
template<typename TEnum>
TEnum DemoDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));		//GetIndexByName 获取enum中名称的索引，返回INDEX_NONE，如果没有找到名称，则可选地返回错误。
}

void DemoDataHandle::InitRecordData()
{
	//RecordName = FString("");

	//获取语言
	FString Culture;

	//读取存档数据
	DemoSingleton<DemoJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);

	//初始化语言
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	// 输出一下
	DemoHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);

	// 循环读取 RecordDataList
	for (TArray<FString>::TIterator It(RecordDataList); It; It++)
	{
		DemoHelper::Debug(*It, 20.f);
	}
}


//void DemoDataHandle::InitializedMenuAudio()
//{
//	//获取MenuStyle
//	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");
//
//	//添加资源文件到资源列表
//	TArray<USoundCue*> MusicList;
//	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));
//
//	TArray<USoundCue*> SoundList;
//	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
//	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
//	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));
//
//	//添加资源到Map
//	MenuAudioResource.Add(FString("Music"), MusicList);
//	MenuAudioResource.Add(FString("Sound"), SoundList);
//
//	//重置一下声音
//	ResetMenuVolume(MusicVolume, SoundVolume);
//}
//
//void DemoDataHandle::InitializeGameData()
//{
//	//初始化物品属性图
//	InitObjectAttr();
//	//初始化资源属性图
//	InitResourceAttrMap();
//	//初始化合成表图
//	InitCompoundTableMap();
//	//初始化游戏声音数据
//	InitializeGameAudio();
//}
//
//void DemoDataHandle::AddNewRecord()
//{
//	//将现在的存档名添加到数组
//	RecordDataList.Add(RecordName);
//	//更新json数据
//	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
//}
//
//void DemoDataHandle::InitObjectAttr()
//{
//	DemoSingleton<DemoJsonHandle>::Get()->ObjectAttrJsonRead(ObjectAttrMap);
//	//获取GameStyle
//	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");
//	//填充笔刷数组
//	ObjectBrushList.Add(&GameStyle->EmptyBrush);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);
//
//	////动态生成Object的图片Brush,这段代码会引起奔溃
//	//for (int i = 1; i < ObjectAttrMap.Num(); ++i) {
//	//	//测试函数,动态创建FSlateBrush,一定要创建指针,否则会在函数结束时销毁资源
//	//	FSlateBrush* ObjectBrush = new FSlateBrush();
//	//	ObjectBrush->ImageSize = FVector2D(80.f, 80.f);
//	//	ObjectBrush->DrawAs = ESlateBrushDrawType::Image;
//	//	UTexture2D* ObjectTex = LoadObject<UTexture2D>(NULL, *(*ObjectAttrMap.Find(i))->TexPath);
//	//	ObjectBrush->SetResourceObject(ObjectTex);
//	//	ObjectBrushList.Add(ObjectBrush);
//	//}
//}
//
//void DemoDataHandle::InitResourceAttrMap()
//{
//	DemoSingleton<DemoJsonHandle>::Get()->ResourceAttrJsonRead(ResourceAttrMap);
//}
//
//void DemoDataHandle::InitCompoundTableMap()
//{
//	DemoSingleton<DemoJsonHandle>::Get()->CompoundTableJsonRead(CompoundTableMap);
//}
//
//void DemoDataHandle::InitializeGameAudio()
//{
//	//获取混音器和音类
//	DemoSoundMix = LoadObject<USoundMix>(NULL, TEXT("SoundMix'/Game/Blueprint/Sound/DemoSoundMix.DemoSoundMix'"));
//	DemoMusicClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/DemoMusicClass.DemoMusicClass'"));
//	DemoSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/DemoSoundClass.DemoSoundClass'"));
//
//	//获取音乐设备
//	AudioDevice = GEngine->GetMainAudioDevice();
//
//	//推送混音器到设备
//	AudioDevice->PushSoundMixModifier(DemoSoundMix);
//
//	//根据音量设置一次声音
//	ResetGameVolume(MusicVolume, SoundVolume);
//}

