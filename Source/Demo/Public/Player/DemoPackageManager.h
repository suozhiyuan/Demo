// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "UI/Widget/Package/SDemoContainerBaseWidget.h"

class SDemoContainerBaseWidget;
/**
 *
 */
class DEMO_API DemoPackageManager
{
public:
	DemoPackageManager();

	static void Initialize();

	static TSharedPtr<DemoPackageManager> Get();

	//�������
	void InsertContainer(TSharedPtr<class SDemoContainerBaseWidget> Container, EContainerType::Type InsertType);

	//������ͣ��������ɫ
	void UpdateHovered(FVector2D MousePos, FGeometry PackGeo);

	//����¼�,���������λ�ú�PackageWidget��Geometry
	void LeftOption(FVector2D MousePos, FGeometry PackGeo);

	//�Ҽ��¼�,���������λ�ú�PackageWidget��Geometry
	void RightOption(FVector2D MousePos, FGeometry PackGeo);

	//�Ƿ��в�����Ʒ�Ŀռ䣬�ṩ���ⲿ����
	bool SearchFreeSpace(int ObjectID);

	//�����Ʒ
	void AddObject(int ObjectID);

	//�Զ���,����������ID,�����Ƿ�ɹ��Ե�
	bool EatUpEvent(int ShortcutID);

//	//���ش浵
//	void LoadRecord(TArray<int32>* InputIndex, TArray<int32>* InputNum, TArray<int32>* NormalIndex, TArray<int32>* NormalNum, TArray<int32>* ShortcutIndex, TArray<int32>* ShortcutNum);
//
//	void SaveData(TArray<int32>& InputIndex, TArray<int32>& InputNum, TArray<int32>& NormalIndex, TArray<int32>& NormalNum, TArray<int32>& ShortcutIndex, TArray<int32>& ShortcutNum);

public:

	//����ϵ���ƷID
	int ObjectIndex;
	//����ϵ���Ʒ����
	int ObjectNum;

	//������Ʒί��,�󶨵ķ�����PlayerState��PlayerThrowObject
	FThrowObject PlayerThrowObject;
	//�޸Ŀ������Ϣί��
	FPackShortChange ChangeHandObject;

private:

	//����ʵ������
	static TSharedRef<DemoPackageManager> Create();

	//��ȡ���ָ�������
	TSharedPtr<SDemoContainerBaseWidget> LocateContainer(FVector2D MousePos, FGeometry PackGeo);

	//������Ʒ�¼�
	void ThrowObject(int ObjectID, int Num);

	//�ϳ���ȡ�¼�
	void CompoundOutput(int ObjectID, int Num);

	//�ϳ������¼�
	void CompoundInput();

	//������任�¼�
	void PackShortChange(int ShortcutID, int ObjectID, int ObjectNum);

	//��ȡ�Ƿ���Ե���
	bool MultiplyAble(int ObjectID);
	
	/**
	 * @brief �Ƿ��в�����Ʒ�Ŀռ�,ÿ��ֻ�����һ��,���ؿ��Բ�����Ǹ�����
	 * @param ObjectID ��ƷID
	 * @param FreeContainer ����������
	 * @return 
	 */
	bool SearchFreeSpace(int ObjectID, TSharedPtr<SDemoContainerBaseWidget>& FreeContainer);

private:

	//����ָ��
	static TSharedPtr<DemoPackageManager> PackageInstance;

	//�����б�
	TArray<TSharedPtr<SDemoContainerBaseWidget>> InputContainerList;		// ���������б�
	TArray<TSharedPtr<SDemoContainerBaseWidget>> NormalContainerList;		// �����������б�
	TArray<TSharedPtr<SDemoContainerBaseWidget>> ShortcutContainerList;		// ����������б�
	//�������ֻ��һ��
	TSharedPtr<SDemoContainerBaseWidget> OutputContainer;

	//��һ����ͣ������
	TSharedPtr<SDemoContainerBaseWidget> LastHoveredCon;

};
