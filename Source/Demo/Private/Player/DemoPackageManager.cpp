// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DemoPackageManager.h"

#include "Data/DemoDataHandle.h"
#include "UI/Widget/Package/SDemoContainerBaseWidget.h"

//��ʼʱ�Ե���ָ�븳ֵ
TSharedPtr<DemoPackageManager> DemoPackageManager::PackageInstance = NULL;

void DemoPackageManager::Initialize()
{
	if (!PackageInstance.IsValid())
		PackageInstance = Create();
}

TSharedPtr<DemoPackageManager> DemoPackageManager::Get()
{
	Initialize();
	return PackageInstance;
}

TSharedRef<DemoPackageManager> DemoPackageManager::Create()
{
	TSharedRef<DemoPackageManager> PackageRef = MakeShareable(new DemoPackageManager());
	return PackageRef;
}

DemoPackageManager::DemoPackageManager()
{
	//��ʼ����Ʒ������Ϊ0
	ObjectIndex = 0;
	ObjectNum = 0;
}

void DemoPackageManager::InsertContainer(TSharedPtr<class SDemoContainerBaseWidget> Container, EContainerType::Type InsertType)
{
	switch (InsertType)
	{
	case EContainerType::Output:
		OutputContainer = Container;
		OutputContainer->CompoundOutput.BindRaw(this, &DemoPackageManager::CompoundOutput);		// �ϳ����ί�а�
		OutputContainer->ThrowObject.BindRaw(this, &DemoPackageManager::ThrowObject);				// ������Ʒί�а�
		break;
	case EContainerType::Input:
		Container->CompoundInput.BindRaw(this, &DemoPackageManager::CompoundInput);				// �ϳ�����ί�а�
		InputContainerList.Add(Container);
		break;
	case EContainerType::Normal:
		NormalContainerList.Add(Container);
		break;
	case EContainerType::Shortcut:
		Container->PackShortChange.BindRaw(this, &DemoPackageManager::PackShortChange);			// �����ί�а�
		ShortcutContainerList.Add(Container);
		break;
	}
}

void DemoPackageManager::UpdateHovered(FVector2D MousePos, FGeometry PackGeo)
{
	//��ǰ��ͣ������
	TSharedPtr<SDemoContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);

	//�����������
	if (CurrHoveredCon.IsValid())
	{
		//���õ�ǰ������ͣ��ʾ
		CurrHoveredCon->UpdateHovered(true);

		//�����һ��������,�����뵱ǰ��������ͬ
		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get()) 
		{
			//������ͣ��ʾ
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		//��ǰ��������������һ��������,ȡ����һ��������ͣ��ʾ
		if (LastHoveredCon.IsValid()) 
		{
			LastHoveredCon->UpdateHovered(false);
		}
	}

	//������һ��ͣ����
	LastHoveredCon = CurrHoveredCon;
}

void DemoPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	//�Ȼ�ȡ���������
	TSharedPtr<SDemoContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	//�����������,ִ�������¼�
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}

	//������������ڲ���������Ʒ��Ϊ��
	if (!ClickedContainer.IsValid() && ObjectIndex != 0)
	{
		//����Ʒ����
		ThrowObject(ObjectIndex, ObjectNum);

		//������Ʒ
		ObjectIndex = ObjectNum = 0;
	}
}

void DemoPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	//�Ȼ�ȡ���������
	TSharedPtr<SDemoContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);

	//�����������,ִ�������¼�
	if (ClickedContainer.IsValid()) 
	{
		ClickedContainer->RightOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
}

TSharedPtr<SDemoContainerBaseWidget> DemoPackageManager::LocateContainer(FVector2D MousePos, FGeometry PackGeo)
{
	//�����ҵ�ָ�������
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) 
	{
		//��ȡ����
		//FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);					// GetCachedGeometry 4.23 �Ѿ�����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetTickSpaceGeometry().AbsolutePosition);		// ȡ���ӵľ������� ����ê��
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);														// ��������
		//�ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)	// ����������ڲ��ڸ��ӷ�Χ��
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) 
	{
		//��ȡ����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//�ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) 
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) 
	{
		//��ȡ����
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//�ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) 
		{
			return *It;
		}
	}

	//���ﴦ�����������
	//��ȡ����
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
	//�ж����λ���Ƿ���������,�ڵĻ�ֱ�ӷ����������
	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) 
	{
		return OutputContainer;
	}

	// ��������겻���κ�һ�������ڣ����ؿ�
	return nullptr;
}

// ���ö�����Ʒί��
void DemoPackageManager::ThrowObject(int ObjectID, int Num)
{
	PlayerThrowObject.ExecuteIfBound(ObjectID, Num);
}

// ���ÿ����ί��
void DemoPackageManager::PackShortChange(int ShortcutID, int ObjectID, int ObjectNum1)
{
	//ִ��ί��,�󶨵ķ�����PlayerState��ChangeHandObject,��playercharacter�½��а�
	ChangeHandObject.ExecuteIfBound(ShortcutID, ObjectID, ObjectNum1);
}

// �ϳ�������ó���ͬʱ���ٺϳɲ���
void DemoPackageManager::CompoundOutput(int ObjectID, int Num)
{
	//����ϳɽ��Ϊ0,ֱ��return
	if (ObjectID == 0) return;

	//�ϳɱ�ṹ���飬���ϳ�����9����Ʒ��ID��¼
	TArray<int> TableMap;
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) 
	{
		TableMap.Add((*It)->GetIndex());
	}
	TableMap.Add(ObjectID);		// ���ϳɽ����ӵ���ߣ���10������

	//��������������
	TArray<int> ExpendMap;

	//�����ҳ����ϵĺϳɱ����õ���������������
	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(DemoDataHandle::Get()->CompoundTableMap); It; ++It) 
	{
		//����ҵ����ϵ�ֱ������ѭ��
		if ((*It)->DetectExpend(&TableMap, Num, ExpendMap)) break;
	}

	//�����������Ԫ����������9,ֱ��return
	if (ExpendMap.Num() != 9) return;

	//ѭ�����úϳ���������
	for (int i = 0; i < 9; ++i) 
	{
		//���ԭ��������ȥ���������Ѿ�С�ڵ���0,ֱ�Ӱ���ƷID����Ϊ0
		int InputID = (InputContainerList[i]->GetNum() - ExpendMap[i] <= 0) ? 0 : InputContainerList[i]->GetIndex();
		int InputNum = (InputID == 0) ? 0 : (InputContainerList[i]->GetNum() - ExpendMap[i]);

		//���ò���
		InputContainerList[i]->ResetContainerPara(InputID, InputNum);
	}
}

// �ϳ�����
void DemoPackageManager::CompoundInput()
{
	//��ȡ�ϳ�̨9����������Ʒid������д����������
	TArray<int> IDMap;
	TArray<int> NumMap;

	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) 
	{
		IDMap.Add((*It)->GetIndex());
		NumMap.Add((*It)->GetNum());
	}

	//���������������ID������
	int OutputIndex = 0;
	int OutputNum = 0;

	//�����ϳɱ���м��
	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(DemoDataHandle::Get()->CompoundTableMap); It; ++It) 
	{
		(*It)->DetectTable(&IDMap, &NumMap, OutputIndex, OutputNum);

		//�����������,ֱ������ѭ��
		if (OutputIndex != 0 && OutputNum != 0) break;
	}

	//�����OutputContainer���и�ֵ
	//���ж��Ƿ���Ե���
	if (MultiplyAble(OutputIndex)) 
	{
		//���Ե��ӵĻ���ֱ�Ӹ�ֵ,����0,0
		OutputContainer->ResetContainerPara(OutputIndex, OutputNum);
	}
	else 
	{
		//�����Ե��ӵĻ�ֻ���һ��
		OutputContainer->ResetContainerPara(OutputIndex, 1);
	}
}

// ��ȡ�Ƿ���Ե���
bool DemoPackageManager::MultiplyAble(int ObjectID)
{
	//��ȡ��Ʒ����
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	//�����Ƿ����������߹���
	return (ObjectAttr->ObjectType != EObjectType::Tool && ObjectAttr->ObjectType != EObjectType::Weapon);
}

bool DemoPackageManager::SearchFreeSpace(int ObjectID, TSharedPtr<SDemoContainerBaseWidget>& FreeContainer)
{
	//����������
	TSharedPtr<SDemoContainerBaseWidget> EmptyContainer;

	// �������������Ϊ���������е�ǰ��Ʒ������������
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) 
	{
		//�����������������ֱ�Ӹ�ֵ
		if (!EmptyContainer.IsValid()) 
		{
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}
		//�������������û������
		if (!FreeContainer.IsValid())
		{
			//��������������Ʒ��������ƷID��ͬ�����пռ�,ֱ��ָ��
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
	}

	// ������������
	for (TArray<TSharedPtr<SDemoContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) 
	{
		//���������������
		if (!EmptyContainer.IsValid()) 
		{
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}
		//�������������û������
		if (!FreeContainer.IsValid())
		{
			//��������������Ʒ��������ƷID��ͬ�����пռ�,ֱ��ָ��
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
	}

	//�����е�����˵����Ҫָ��������
	if (EmptyContainer.IsValid()) 
	{
		FreeContainer = EmptyContainer;		// ����һ������������
		return true;
	}
	//�������������û��,����false
	return false;
}

bool DemoPackageManager::SearchFreeSpace(int ObjectID)
{
	TSharedPtr<SDemoContainerBaseWidget> FreeContainer;
	return SearchFreeSpace(ObjectID, FreeContainer);
}

void DemoPackageManager::AddObject(int ObjectID)
{
	TSharedPtr<SDemoContainerBaseWidget> FreeContainer;
	if (SearchFreeSpace(ObjectID, FreeContainer)) 
	{
		//�����Ʒ������
		FreeContainer->AddObject(ObjectID);
	}
}

bool DemoPackageManager::EatUpEvent(int ShortcutID)
{
	//��ȡ��Ʒ����
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ShortcutContainerList[ShortcutID]->GetIndex());

	//��������Ʒ��ʳ��
	if (ObjectAttr->ObjectType == EObjectType::Food)
	{
		//�Թ����µ���Ʒ����
		int NewNum = (ShortcutContainerList[ShortcutID]->GetNum() - 1) < 0 ? 0 : (ShortcutContainerList[ShortcutID]->GetNum() - 1);

		//�µ���ƷID
		int NewIndex = NewNum == 0 ? 0 : ShortcutContainerList[ShortcutID]->GetIndex();

		//����������������������
		ShortcutContainerList[ShortcutID]->ResetContainerPara(NewIndex, NewNum);

		//���سɹ��Ե�ʳ��
		return true;
	}
	return false;
}

//void DemoPackageManager::LoadRecord(TArray<int32>* InputIndex, TArray<int32>* InputNum, TArray<int32>* NormalIndex, TArray<int32>* NormalNum, TArray<int32>* ShortcutIndex, TArray<int32>* ShortcutNum)
//{
//	for (int i = 0; i < InputContainerList.Num(); ++i)
//	{
//		if ((*InputIndex)[i] != 0) InputContainerList[i]->ResetContainerPara((*InputIndex)[i], (*InputNum)[i]);
//	}
//	for (int i = 0; i < NormalContainerList.Num(); ++i) {
//		if ((*NormalIndex)[i] != 0) NormalContainerList[i]->ResetContainerPara((*NormalIndex)[i], (*NormalNum)[i]);
//	}
//	for (int i = 0; i < ShortcutContainerList.Num(); ++i) {
//		if ((*ShortcutIndex)[i] != 0) ShortcutContainerList[i]->ResetContainerPara((*ShortcutIndex)[i], (*ShortcutNum)[i]);
//	}
//}
//
//void DemoPackageManager::SaveData(TArray<int32>& InputIndex, TArray<int32>& InputNum, TArray<int32>& NormalIndex, TArray<int32>& NormalNum, TArray<int32>& ShortcutIndex, TArray<int32>& ShortcutNum)
//{
//	for (int i = 0; i < InputContainerList.Num(); ++i)
//	{
//		InputIndex.Add(InputContainerList[i]->GetIndex());
//		InputNum.Add(InputContainerList[i]->GetNum());
//	}
//	for (int i = 0; i < NormalContainerList.Num(); ++i) {
//		NormalIndex.Add(NormalContainerList[i]->GetIndex());
//		NormalNum.Add(NormalContainerList[i]->GetNum());
//	}
//	for (int i = 0; i < ShortcutContainerList.Num(); ++i) {
//		ShortcutIndex.Add(ShortcutContainerList[i]->GetIndex());
//		ShortcutNum.Add(ShortcutContainerList[i]->GetNum());
//	}
//}
