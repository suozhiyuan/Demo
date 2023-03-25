// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DomeJsonHandle.h"

#include "Common/DemoHelper.h"


DemoJsonHandle::DemoJsonHandle()
{

	RecordDataFileName = FString("RecordData.json");				//�浵�ļ���
	ObjectAttrFileName = FString("ObjectAttribute.json");
	//ResourceAttrFileName = FString("ResourceAttribute.json");
	//CompoundTableFileName = FString("CompoundTable.json");

	RelativePath = FString("Res/ConfigData/");			//���·��

}

// �����浵����
void DemoJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);					// ��ȡJson�ļ����ַ���

	TArray<TSharedPtr<FJsonValue>> JsonParsed;														// �����������������
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);		// �����ݴ浽 TJsonReader ָ��

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))		// �������ɹ�����true
	{
		//��ȡ����
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));					// GetStringField��ͨ�� Key ��ȡһ�� String ���͵ı���
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));			// GetNumberField��ͨ�� Key ��ȡһ�� Int ���͵ı���
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));

		//��ȡ�浵����
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));	// GetArrayField��ͨ�� Key ��ȡһ�� Array ���͵ı���
		for (int i = 0; i < RecordDataArray.Num(); ++i) 
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));	// FromInt��������ת��Ϊ�ַ���
			RecordDataList.Add(RecordDataName);
		}
	}
	else 
	{
		DemoHelper::Debug(FString("Deserialize Failed"));
	}

}

// �޸Ĵ浵
void DemoJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);				// SetStringField:���һ����Ϊ ����1 ���ֶΣ�ֵΪ ����2 �ַ�������
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);			// SetNumberField :���һ����Ϊ ����1 ���ֶΣ�ֵΪ ����2 ��������
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;
	for (int i = 0; i < RecordDataList->Num(); ++i) {
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}

	// RecordDataArray ǰ����ͷָ�� RecordData
	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);		// SetArrayField :���һ����Ϊ ����1 ���ֶΣ�ֵΪ ����2 ��������
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	// ��ӽ�������
	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);
	JsonObject->SetArrayField("T", BaseDataArray);

	// FJsonObject ת��Ϊ Json ��ʽ���ַ���
	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

	//DemoHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	//ȥ�������ַ�
	JsonStr.RemoveAt(0, 8);					// ǰ8���ַ�
	JsonStr.RemoveFromEnd(FString("}"));		// ��ߵ� ������

	//DemoHelper::Debug(FString("Final Str : " + JsonStr), 60.f);

	//�� Json ��ʽ���ַ��� д�� Json �ļ�
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);
}

void DemoJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;														// �����������������
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);		// �����ݴ浽 TJsonReader ָ��

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); ++i)
		{
			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			FText EN = FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr = ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack = ObjectAttr[3]->AsObject()->GetIntegerField("PlantAttack");
			int MetalAttcck = ObjectAttr[4]->AsObject()->GetIntegerField("MetalAttcck");
			int AnimalAttack = ObjectAttr[5]->AsObject()->GetIntegerField("AnimalAttack");
			int AffectRange = ObjectAttr[6]->AsObject()->GetIntegerField("AffectRange");
			FString TexPath = ObjectAttr[7]->AsObject()->GetStringField("TexPath");

			EObjectType::Type ObjectType = StringToObjectType(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr = MakeShareable(new ObjectAttribute(EN, ZH, ObjectType, PlantAttack, MetalAttcck, AnimalAttack, AffectRange, TexPath));

			ObjectAttrMap.Add(i, ObjectAttrPtr);
		}
	}
	else 
	{
		DemoHelper::Debug(FString("Deserialize Failed"));
	}

}

//void DemoJsonHandle::ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap)
//{
//	FString JsonValue;
//	LoadStringFromFile(ResourceAttrFileName, RelativePath, JsonValue);
//
//	TArray<TSharedPtr<FJsonValue>> JsonParsed;
//	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
//
//	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
//	{
//		for (int i = 0; i < JsonParsed.Num(); ++i) {
//			//��Դû�����0,��1��ʼ
//			TArray<TSharedPtr<FJsonValue>> ResourceAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i + 1));
//			FText EN = FText::FromString(ResourceAttr[0]->AsObject()->GetStringField("EN"));
//			FText ZH = FText::FromString(ResourceAttr[1]->AsObject()->GetStringField("ZH"));
//			EResourceType::Type ResourceType = StringToResourceType(ResourceAttr[2]->AsObject()->GetStringField("ResourceType"));
//			int HP = ResourceAttr[3]->AsObject()->GetIntegerField("HP");
//
//			TArray<TArray<int>> FlobObjectInfoArray;
//
//			TArray<TSharedPtr<FJsonValue>> FlobObjectInfo = ResourceAttr[4]->AsObject()->GetArrayField(FString("FlobObjectInfo"));
//
//			for (int j = 0; j < FlobObjectInfo.Num(); ++j) {
//
//				FString FlobObjectInfoItem = FlobObjectInfo[j]->AsObject()->GetStringField(FString::FromInt(j));
//				FString ObjectIndexStr;
//				FString RangeStr;
//				FString RangeMinStr;
//				FString RangeMaxStr;
//				FlobObjectInfoItem.Split(FString("_"), &ObjectIndexStr, &RangeStr);
//				RangeStr.Split(FString(","), &RangeMinStr, &RangeMaxStr);
//
//				TArray<int> FlobObjectInfoList;
//
//				FlobObjectInfoList.Add(FCString::Atoi(*ObjectIndexStr));
//				FlobObjectInfoList.Add(FCString::Atoi(*RangeMinStr));
//				FlobObjectInfoList.Add(FCString::Atoi(*RangeMaxStr));
//
//				FlobObjectInfoArray.Add(FlobObjectInfoList);
//			}
//
//			TSharedPtr<ResourceAttribute> ResourceAttrPtr = MakeShareable(new ResourceAttribute(EN, ZH, ResourceType, HP, &FlobObjectInfoArray));
//
//			ResourceAttrMap.Add(i + 1, ResourceAttrPtr);
//		}
//	}
//	else
//	{
//		DemoHelper::Debug(FString("Deserialize Failed"), 10.f);
//	}
//
//}
//
//void DemoJsonHandle::CompoundTableJsonRead(TArray<TSharedPtr<CompoundTable>>& CompoundTableMap)
//{
//	FString JsonValue;
//	LoadStringFromFile(CompoundTableFileName, RelativePath, JsonValue);
//
//	TArray<TSharedPtr<FJsonValue>> JsonParsed;
//	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
//
//	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
//	{
//
//		for (int i = 0; i < JsonParsed.Num(); ++i) {
//			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
//
//			TArray<int> CompoundTableArr;
//
//			for (int j = 0; j < 10; ++j) {
//				CompoundTableArr.Add(ObjectAttr[j]->AsObject()->GetIntegerField(FString::FromInt(j)));
//			}
//
//			TSharedPtr<CompoundTable> NewTable = MakeShareable(new CompoundTable(&CompoundTableArr));
//
//			CompoundTableMap.Add(NewTable);
//
//		}
//
//	}
//	else {
//		DemoHelper::Debug(FString("Deserialize Failed"));
//	}
//}

// ��ȡJson�ļ����ַ���
bool DemoJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty()) {
		//��ȡ����·��
		// FString AbsoPath = FPaths::GameContentDir() + RelaPath + FileName;	 // ������(4.18����FPaths::GameContentDir()�ѱ�FPaths::ProjectContentDir()��ȡ������)
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsoPath))	// FileExists ����ҵ����ļ��򷵻�true�����򷵻�false
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))		// LoadFileToString ����һ���ı��ļ���һ��FString���ɹ��ϻ�true
			{
				return true;
			}
			else 
			{
				//���ز��ɹ�
				DemoHelper::Debug(FString("Load Error") + AbsoPath);
			}
		}
		else 
		{
			//����ļ�������
			DemoHelper::Debug(FString("File Not Exist") + AbsoPath);
		}
	}
	return false;
}

// FJsonObjectת��ΪJson��ʽ���ַ���
bool DemoJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);
		return true;
	}
	return false;
}

// �����ַ������ļ�
bool DemoJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty()) 
	{
		if (!FileName.IsEmpty()) 
		{
			FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;

			//����
			if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))		// SaveStringToFile ��FStringд���ļ�
			{

				return true;
			}
			else 
			{
				DemoHelper::Debug(FString("Save") + AbsoPath + FString("-->Failed"), 10.f);
			}
		}

	}
	return false;
}


EObjectType::Type DemoJsonHandle::StringToObjectType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;			// Equals ���ֵ�˳����Դ��ַ����Ƿ��ͬ�ڸ�����Other�ַ���
	if (ArgStr.Equals(FString("Food"))) return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool"))) return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon"))) return EObjectType::Weapon;
	return EObjectType::Normal;
}

//EResourceType::Type DemoJsonHandle::StringToResourceType(const FString ArgStr)
//{
//	if (ArgStr.Equals(FString("Plant"))) return EResourceType::Plant;
//	if (ArgStr.Equals(FString("Metal"))) return EResourceType::Metal;
//	if (ArgStr.Equals(FString("Animal"))) return EResourceType::Animal;
//	return EResourceType::Plant;
//}

