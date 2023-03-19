// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class DEMO_API DemoInternation
{
public:
	static void Register(FText Value)
	{
		return;
	}

};

#define LOCTEXT_NAMESPACE "DemoMenu"	//LocText�������ռ俪ʼ�������·�д�� DemoInternation::Register(NSLOCTEXT ("DemoMenu","Menu", "Menu"));

// ������
DemoInternation::Register(LOCTEXT("Menu", "Menu"));								//�˵�
DemoInternation::Register(LOCTEXT("StartGame", "StartGame"));					//��ʼ��Ϸ
DemoInternation::Register(LOCTEXT("GameOption", "GameOption"));					//��Ϸ����
DemoInternation::Register(LOCTEXT("QuitGame", "QuitGame"));						//�˳���Ϸ
DemoInternation::Register(LOCTEXT("NewGame", "NewGame"));						//����Ϸ
DemoInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));					//���ش浵
DemoInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));				//ѡ��浵

// ������Ϸ����
DemoInternation::Register(LOCTEXT("RecordName", "RecordName"));						//�浵��
DemoInternation::Register(LOCTEXT("EnterGame", "EnterGame"));						//������Ϸ
DemoInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));					//����浵
DemoInternation::Register(LOCTEXT("RecordNameHint", "Input Record Name!");			//����浵��
DemoInternation::Register(LOCTEXT("NameRepeatedHint", "Record Name Repeated!");		//�浵�����ظ�

// ��Ϸ���ý���
DemoInternation::Register(LOCTEXT("Chinese", "Chinese"));			//����
DemoInternation::Register(LOCTEXT("English", "English"));			//Ӣ��
DemoInternation::Register(LOCTEXT("Music", "Music"));				//����
DemoInternation::Register(LOCTEXT("Sound", "Sound"));				//��Ч

// ����
DemoInternation::Register(LOCTEXT("GoBack", "GoBack"));				//����

#undef LOCTEXT_NAMESPACE



#define LOCTEXT_NAMESPACE "DemoGame"
DemoInternation::Register(LOCTEXT("E", "E"));//��
DemoInternation::Register(LOCTEXT("S", "S"));//��
DemoInternation::Register(LOCTEXT("W", "W"));//��
DemoInternation::Register(LOCTEXT("N", "N"));//��

DemoInternation::Register(LOCTEXT("Player", "Player"));//���
DemoInternation::Register(LOCTEXT("Enemy", "Enemy"));//����

DemoInternation::Register(LOCTEXT("EnemyDialogue", ": Fight with me !"));//���˵ĶԻ�
DemoInternation::Register(LOCTEXT("Send", "Send"));//����

DemoInternation::Register(LOCTEXT("GameOption", "GameOption"));//��Ϸ����
DemoInternation::Register(LOCTEXT("SaveGame", "SaveGame"));//������Ϸ
DemoInternation::Register(LOCTEXT("SaveCompleted", "SaveCompleted"));//�������
DemoInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//�˳���Ϸ
DemoInternation::Register(LOCTEXT("GoBack", "GoBack"));//����

#undef LOCTEXT_NAMESPACE
