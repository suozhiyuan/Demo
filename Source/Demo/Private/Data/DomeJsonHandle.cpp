// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DomeJsonHandle.h"

#include "Common/DemoHelper.h"


DemoJsonHandle::DemoJsonHandle()
{

	RecordDataFileName = FString("RecordData.json");				//存档文件名
	ObjectAttrFileName = FString("ObjectAttribute.json");
	//ResourceAttrFileName = FString("ResourceAttribute.json");
	//CompoundTableFileName = FString("CompoundTable.json");

	RelativePath = FString("Res/ConfigData/");			//相对路径

}

// 解析存档方法
void DemoJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);					// 读取Json文件到字符串

	TArray<TSharedPtr<FJsonValue>> JsonParsed;														// 保存解析出来的数据
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);		// 将数据存到 TJsonReader 指针

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))		// 解析，成功返回true
	{
		//获取数据
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));					// GetStringField：通过 Key 获取一个 String 类型的变量
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));			// GetNumberField：通过 Key 获取一个 Int 类型的变量
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));

		//获取存档数据
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));	// GetArrayField：通过 Key 获取一个 Array 类型的变量
		for (int i = 0; i < RecordDataArray.Num(); ++i) 
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));	// FromInt：将整数转换为字符串
			RecordDataList.Add(RecordDataName);
		}
	}
	else 
	{
		DemoHelper::Debug(FString("Deserialize Failed"));
	}

}

// 修改存档
void DemoJsonHandle::UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);				// SetStringField:添加一个名为 参数1 的字段，值为 参数2 字符串类型
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);			// SetNumberField :添加一个名为 参数1 的字段，值为 参数2 数字类型
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

	// RecordDataArray 前方的头指针 RecordData
	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);		// SetArrayField :添加一个名为 参数1 的字段，值为 参数2 数组类型
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	// 添加进总数组
	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);
	JsonObject->SetArrayField("T", BaseDataArray);

	// FJsonObject 转换为 Json 格式的字符串
	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

	//DemoHelper::Debug(FString("Origin Str : " + JsonStr), 60.f);

	//去掉多余字符
	JsonStr.RemoveAt(0, 8);					// 前8个字符
	JsonStr.RemoveFromEnd(FString("}"));		// 后边的 大括号

	//DemoHelper::Debug(FString("Final Str : " + JsonStr), 60.f);

	//将 Json 格式的字符串 写入 Json 文件
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);
}

void DemoJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;														// 保存解析出来的数据
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);		// 将数据存到 TJsonReader 指针

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
//			//资源没有序号0,从1开始
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

// 读取Json文件到字符串
bool DemoJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty()) {
		//获取绝对路径
		// FString AbsoPath = FPaths::GameContentDir() + RelaPath + FileName;	 // 已弃用(4.18，“FPaths::GameContentDir()已被FPaths::ProjectContentDir()所取代。”)
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsoPath))	// FileExists 如果找到该文件则返回true，否则返回false
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))		// LoadFileToString 加载一个文本文件到一个FString，成功赶回true
			{
				return true;
			}
			else 
			{
				//加载不成功
				DemoHelper::Debug(FString("Load Error") + AbsoPath);
			}
		}
		else 
		{
			//输出文件不存在
			DemoHelper::Debug(FString("File Not Exist") + AbsoPath);
		}
	}
	return false;
}

// FJsonObject转换为Json格式的字符串
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

// 保存字符串到文件
bool DemoJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty()) 
	{
		if (!FileName.IsEmpty()) 
		{
			FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;

			//保存
			if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))		// SaveStringToFile 将FString写入文件
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
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;			// Equals 按字典顺序测试此字符串是否等同于给定的Other字符串
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

