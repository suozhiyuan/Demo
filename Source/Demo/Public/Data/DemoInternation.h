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

#define LOCTEXT_NAMESPACE "DemoMenu"	//LocText的命名空间开始，或者下方写成 DemoInternation::Register(NSLOCTEXT ("DemoMenu","Menu", "Menu"));

// 主界面
DemoInternation::Register(LOCTEXT("Menu", "Menu"));								//菜单
DemoInternation::Register(LOCTEXT("StartGame", "StartGame"));					//开始游戏
DemoInternation::Register(LOCTEXT("GameOption", "GameOption"));					//游戏设置
DemoInternation::Register(LOCTEXT("QuitGame", "QuitGame"));						//退出游戏
DemoInternation::Register(LOCTEXT("NewGame", "NewGame"));						//新游戏
DemoInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));					//加载存档
DemoInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));				//选择存档

// 进入游戏界面
DemoInternation::Register(LOCTEXT("RecordName", "RecordName"));						//存档名
DemoInternation::Register(LOCTEXT("EnterGame", "EnterGame"));						//进入游戏
DemoInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));					//进入存档
DemoInternation::Register(LOCTEXT("RecordNameHint", "Input Record Name!");			//输入存档名
DemoInternation::Register(LOCTEXT("NameRepeatedHint", "Record Name Repeated!");		//存档名称重复

// 游戏设置界面
DemoInternation::Register(LOCTEXT("Chinese", "Chinese"));			//中文
DemoInternation::Register(LOCTEXT("English", "English"));			//英文
DemoInternation::Register(LOCTEXT("Music", "Music"));				//音乐
DemoInternation::Register(LOCTEXT("Sound", "Sound"));				//音效

// 公用
DemoInternation::Register(LOCTEXT("GoBack", "GoBack"));				//返回

#undef LOCTEXT_NAMESPACE



#define LOCTEXT_NAMESPACE "DemoGame"
DemoInternation::Register(LOCTEXT("E", "E"));//东
DemoInternation::Register(LOCTEXT("S", "S"));//南
DemoInternation::Register(LOCTEXT("W", "W"));//西
DemoInternation::Register(LOCTEXT("N", "N"));//北

DemoInternation::Register(LOCTEXT("Player", "Player"));//玩家
DemoInternation::Register(LOCTEXT("Enemy", "Enemy"));//敌人

DemoInternation::Register(LOCTEXT("EnemyDialogue", ": Fight with me !"));//敌人的对话
DemoInternation::Register(LOCTEXT("Send", "Send"));//发送

DemoInternation::Register(LOCTEXT("GameOption", "GameOption"));//游戏设置
DemoInternation::Register(LOCTEXT("SaveGame", "SaveGame"));//保存游戏
DemoInternation::Register(LOCTEXT("SaveCompleted", "SaveCompleted"));//保存完毕
DemoInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//退出游戏
DemoInternation::Register(LOCTEXT("GoBack", "GoBack"));//返回

#undef LOCTEXT_NAMESPACE
