// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class USoundCue;
enum class ECultureTeam : uint8;
/**
 * 
 */
class DEMO_API DemoDataHandle
{
public:
	DemoDataHandle();

	static void Initialize();

	static TSharedPtr<DemoDataHandle> Get();

	//�޸���Ӣ��
	void ChangeLocalizationCulture(ECultureTeam Culture);

	//�޸Ĳ˵�����
	void ResetMenuVolume(float MusicVol, float SoundVol);

	////�޸���Ϸ����
	//void ResetGameVolume(float MusicVol, float SoundVol);

public:
	//��ǰ����
	ECultureTeam CurrentCulture;

	//����
	float MusicVolume;
	float SoundVolume;

	//�浵����
	TArray<FString> RecordDataList;

	//�浵��
	FString RecordName;

	//	//��Ʒ����ͼ
//	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;
//	//��Ʒ��ͼ��Դ����
//	TArray<const FSlateBrush*> ObjectBrushList;
//	//��Դ����ͼ
//	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;
//	//�ϳɱ�ͼ
//	TArray<TSharedPtr<CompoundTable>> CompoundTableMap;


private:
	//��������
	static TSharedRef<DemoDataHandle> Create();

	//����enum���ͻ�ȡ�ַ���
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	//�����ַ�����ȡEnumֵ
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);

	//��ʼ���浵����
	void InitRecordData();

	////��Ϸ���ݳ�ʼ��
	//void InitializeGameData();

	//��ʼ��Menu��������
	void InitializedMenuAudio();

//	//��ʼ����Ʒ����ͼ
//	void InitObjectAttr();

//	//��ʼ����Դ����ͼ
//	void InitResourceAttrMap();

//	//��ʼ���ϳɱ�ͼ
//	void InitCompoundTableMap();

//	//��ʼ��Game��������
//	void InitializeGameAudio();

	//	//����´浵��
//	void AddNewRecord();

private:
	static TSharedPtr<DemoDataHandle> DataInstance;

	//����Menu������
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;

	//��ȡMenuStyle,�������������ļ�
	const struct FDemoMenuStyle* MenuStyle;

	////��ȡGameStyle
	//const struct FDemoGameStyle* GameStyle;
	////�������
	//class USoundMix* DemoSoundMix;
	//class USoundClass* DemoMusicClass;
	//USoundClass* DemoSoundClass;
	//class FAudioDevice* AudioDevice;









};
