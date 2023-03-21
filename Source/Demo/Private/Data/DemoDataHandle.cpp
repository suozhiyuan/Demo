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
	//��ʼ���浵����
	InitRecordData();

	//��ʼ����������
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

// �޸���Ӣ��
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
	//��ֵ
	CurrentCulture = Culture;

	//���´浵����
	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

TSharedRef<DemoDataHandle> DemoDataHandle::Create()
{
	TSharedRef<DemoDataHandle> DataRef = MakeShareable(new DemoDataHandle());	// MakeShareable ���Դ�������ָ���빲������
	return DataRef;
}

// �޸Ĳ˵�����
void DemoDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		////ѭ�����ñ�������
		//for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		//{
		//	//��������
		//	(*It)->VolumeMultiplier = MusicVolume;
		//}
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		//{
		//	//ָ���ָ��
		//	(*It)->VolumeMultiplier = SoundVolume;
		//}
	}
	
	//���´浵����
	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

//void DemoDataHandle::ResetGameVolume(float MusicVol, float SoundVol)
//{
//	if (MusicVol > 0)
//	{
//		MusicVolume = MusicVol;
//		//ʹ�û�����������
//		AudioDevice->SetSoundMixClassOverride(DemoSoundMix, DemoMusicClass, MusicVolume, 1.f, 0.2f, false);
//	}
//	if (SoundVol > 0)
//	{
//		SoundVolume = SoundVol;
//		//ʹ�û�����������
//		AudioDevice->SetSoundMixClassOverride(DemoSoundMix, DemoSoundClass, SoundVolume, 1.f, 0.2f, false);
//	}
//	//���´浵����
//	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
//}


// ����enum���ͻ�ȡ�ַ���
template<typename TEnum>
FString DemoDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);		// ��ͨ�� FindObject �� ANY_PACKAGE ����� Name
	if (!EnumPtr) 
	{
		return FString("InValid");
	}
	//return EnumPtr->GetEnumName((int32)Value);			// GetEnumName ������
	return EnumPtr->GetNameStringByIndex((int32)Value);
}

// �����ַ�����ȡEnumֵ
template<typename TEnum>
TEnum DemoDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));		//GetIndexByName ��ȡenum�����Ƶ�����������INDEX_NONE�����û���ҵ����ƣ����ѡ�ط��ش���
}

void DemoDataHandle::InitRecordData()
{
	//RecordName = FString("");

	//��ȡ����
	FString Culture;

	//��ȡ�浵����
	DemoSingleton<DemoJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);

	//��ʼ������
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	// ���һ��
	DemoHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);

	// ѭ����ȡ RecordDataList
	for (TArray<FString>::TIterator It(RecordDataList); It; It++)
	{
		DemoHelper::Debug(*It, 20.f);
	}
}


//void DemoDataHandle::InitializedMenuAudio()
//{
//	//��ȡMenuStyle
//	MenuStyle = &DemoStyle::Get().GetWidgetStyle<FDemoMenuStyle>("BPDemoMenuStyle");
//
//	//�����Դ�ļ�����Դ�б�
//	TArray<USoundCue*> MusicList;
//	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));
//
//	TArray<USoundCue*> SoundList;
//	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
//	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
//	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));
//
//	//�����Դ��Map
//	MenuAudioResource.Add(FString("Music"), MusicList);
//	MenuAudioResource.Add(FString("Sound"), SoundList);
//
//	//����һ������
//	ResetMenuVolume(MusicVolume, SoundVolume);
//}
//
//void DemoDataHandle::InitializeGameData()
//{
//	//��ʼ����Ʒ����ͼ
//	InitObjectAttr();
//	//��ʼ����Դ����ͼ
//	InitResourceAttrMap();
//	//��ʼ���ϳɱ�ͼ
//	InitCompoundTableMap();
//	//��ʼ����Ϸ��������
//	InitializeGameAudio();
//}
//
//void DemoDataHandle::AddNewRecord()
//{
//	//�����ڵĴ浵����ӵ�����
//	RecordDataList.Add(RecordName);
//	//����json����
//	DemoSingleton<DemoJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
//}
//
//void DemoDataHandle::InitObjectAttr()
//{
//	DemoSingleton<DemoJsonHandle>::Get()->ObjectAttrJsonRead(ObjectAttrMap);
//	//��ȡGameStyle
//	GameStyle = &DemoStyle::Get().GetWidgetStyle<FDemoGameStyle>("BPDemoGameStyle");
//	//����ˢ����
//	ObjectBrushList.Add(&GameStyle->EmptyBrush);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
//	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);
//
//	////��̬����Object��ͼƬBrush,��δ����������
//	//for (int i = 1; i < ObjectAttrMap.Num(); ++i) {
//	//	//���Ժ���,��̬����FSlateBrush,һ��Ҫ����ָ��,������ں�������ʱ������Դ
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
//	//��ȡ������������
//	DemoSoundMix = LoadObject<USoundMix>(NULL, TEXT("SoundMix'/Game/Blueprint/Sound/DemoSoundMix.DemoSoundMix'"));
//	DemoMusicClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/DemoMusicClass.DemoMusicClass'"));
//	DemoSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/DemoSoundClass.DemoSoundClass'"));
//
//	//��ȡ�����豸
//	AudioDevice = GEngine->GetMainAudioDevice();
//
//	//���ͻ��������豸
//	AudioDevice->PushSoundMixModifier(DemoSoundMix);
//
//	//������������һ������
//	ResetGameVolume(MusicVolume, SoundVolume);
//}

