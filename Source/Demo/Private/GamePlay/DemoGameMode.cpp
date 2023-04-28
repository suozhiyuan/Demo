// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/DemoGameMode.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlay/DemoGameInstance.h"
#include "Common/DemoHelper.h"
#include "Common/DemoSceneCapture2D.h"
#include "Data/DemoDataHandle.h"
#include "Player/DemoPlayerCharacter.h"

#include "Player/DemoPlayerController.h"
#include "Player/DemoPlayerState.h"
#include "UI/HUD/DemoGameHUD.h"
#include "Data/DemoDataHandle.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "GamePlay/DemoSaveGame.h"
#include "Pickup/DemoPickupStone.h"
#include "Pickup/DemoPickupWood.h"
#include "Player/DemoPackageManager.h"
#include "Resource/DemoResourceRock.h"
#include "Resource/DemoResourceTree.h"


ADemoGameMode::ADemoGameMode()
{
	//允许开启tick函数
	PrimaryActorTick.bCanEverTick = true;

	//添加组件
	HUDClass = ADemoGameHUD::StaticClass();
	PlayerControllerClass = ADemoPlayerController::StaticClass();
	PlayerStateClass = ADemoPlayerState::StaticClass();
	DefaultPawnClass = ADemoPlayerCharacter::StaticClass();

	//开始没有初始化背包
	IsInitPackage = false;

	//小地图还没生成
	IsCreateMiniMap = false;

	//开始设置不需要加载存档
	IsNeedLoadRecord = false;
}

void ADemoGameMode::Tick(float DeltaSeconds)
{
	//初始化与更新小地图摄像机
	InitializeMiniMapCamera();

	//给背包加载存档, 第二帧再执行
	LoadRecordPackage();

	//初始化背包
	InitializePackage();
}

void ADemoGameMode::InitGamePlayModule()
{
	//添加引用
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPCharacter = Cast<ADemoPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SPState = Cast<ADemoPlayerState>(SPController->PlayerState);
}

void ADemoGameMode::SaveGame()
{
	//如果存档名是Default,不进行保存
	if (DemoDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	//创建一个新的存档
	UDemoSaveGame* NewRecord = Cast<UDemoSaveGame>(UGameplayStatics::CreateSaveGameObject(UDemoSaveGame::StaticClass()));

	//对存档进行赋值
	//设置玩家位置和血量
	NewRecord->PlayerLocation = SPCharacter->GetActorLocation();
	SPState->SaveState(NewRecord->PlayerHP, NewRecord->PlayerHunger);

	//循环设置敌人
	for (TActorIterator<ADemoEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
	{
		NewRecord->EnemyLoaction.Add((*EnemyIt)->GetActorLocation());
		NewRecord->EnemyHP.Add((*EnemyIt)->GetHP());
	}

	//循环设置岩石
	for (TActorIterator<ADemoResourceRock> RockIt(GetWorld()); RockIt; ++RockIt)
	{
		NewRecord->ResourceRock.Add((*RockIt)->GetActorLocation());
	}

	//循环设置树木
	for (TActorIterator<ADemoResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt)
	{
		NewRecord->ResourceTree.Add((*TreeIt)->GetActorLocation());
	}

	//循环设置拾取物品石头
	for (TActorIterator<ADemoPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) 
	{
		NewRecord->PickupStone.Add((*StoneIt)->GetActorLocation());
	}

	//循环设置拾取物品木头
	for (TActorIterator<ADemoPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt)
	{
		NewRecord->PickupWood.Add((*WoodIt)->GetActorLocation());
	}

	//获取背包数据
	DemoPackageManager::Get()->SaveData(NewRecord->InputIndex, NewRecord->InputNum, NewRecord->NormalIndex, NewRecord->NormalNum, NewRecord->ShortcutIndex, NewRecord->ShortcutNum);

	//查看是否已经有存档存在
	if (UGameplayStatics::DoesSaveGameExist(DemoDataHandle::Get()->RecordName, 0)) 
	{
		//有的话先删除
		UGameplayStatics::DeleteGameInSlot(DemoDataHandle::Get()->RecordName, 0);
	}
	//保存存档
	UGameplayStatics::SaveGameToSlot(NewRecord, DemoDataHandle::Get()->RecordName, 0);

	//查看json是否已经有这个存档
	bool IsRecordExist = false;
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It)
	{
		//只要有一个相同,就跳出
		if ((*It).Equals(DemoDataHandle::Get()->RecordName)) 
		{
			IsRecordExist = true;
			break;
		}
	}
	//如果存档不存在,让数据管理类添加存档到json
	if (!IsRecordExist) DemoDataHandle::Get()->AddNewRecord();
}


void ADemoGameMode::BeginPlay()
{
	// 测试代码，DataHandle 和 GameInstance 同样都有跨场景保存数据的功能
	DemoHelper::Debug(FString("DataHandle : ") + DemoDataHandle::Get()->RecordName, 30.f);
	DemoHelper::Debug(FString("GameInstance : ") + Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName, 30.f);

	// 初始化游戏数据
	//DemoDataHandle::Get()->InitializeGameData();

	if (!SPController) InitGamePlayModule();

	//播放背景音乐
	USoundWave* BGMusic = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Res/Sound/GameSound/GameBG.GameBG'"));		// 加载音乐资源
	BGMusic->bLooping = true;																										// 设置是否循环
	UGameplayStatics::PlaySound2D(GetWorld(), BGMusic, 0.1f);															// 播放，参数3为初始音量，默认值是1

	LoadRecord();
}

void ADemoGameMode::InitializePackage()
{
	if (IsInitPackage) return;

	//叫PackageWidget初始化背包管理器
	InitPackageManager.ExecuteIfBound();

	//绑定丢弃物品委托
	DemoPackageManager::Get()->PlayerThrowObject.BindUObject(SPCharacter, &ADemoPlayerCharacter::PlayerThrowObject);
	//绑定修改快捷栏信息委托
	DemoPackageManager::Get()->ChangeHandObject.BindUObject(SPState, &ADemoPlayerState::ChangeHandObject);

	IsInitPackage = true;
}

void ADemoGameMode::InitializeMiniMapCamera()
{
	//如果地图正交像机还不存在 并且 世界已经存在
	if (!IsCreateMiniMap && GetWorld())
	{
		//生成小地图摄像机
		MiniMapCamera = GetWorld()->SpawnActor<ADemoSceneCapture2D>(ADemoSceneCapture2D::StaticClass());

		// 独立窗口运行游戏时会崩溃
		//运行委托给 MiniMapWidget 传递渲染的 MiniMapTex
		//RegisterMiniMap.ExecuteIfBound(MiniMapCamera->GetMiniMapTex());

		//绑定修改小地图视野的委托
		SPController->UpdateMiniMapWidth.BindUObject(MiniMapCamera, &ADemoSceneCapture2D::UpdateMiniMapWidth);

		//设置已经生成小地图
		IsCreateMiniMap = true;
	}

	//如果小地图已经创建
	if (IsCreateMiniMap)
	{
		//每帧更新小地图摄像机的位置和旋转
		MiniMapCamera->UpdateTransform(SPCharacter->GetActorLocation(), SPCharacter->GetActorRotation());

		TArray<FVector2D> EnemyPosList;		// 敌人位置
		TArray<bool> EnemyLockList;			// 是否锁定
		TArray<float> EnemyRotateList;		// 敌人旋转

		//获取场景中的敌人
		for (TActorIterator<ADemoEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
		{
			// 计算相对位置
			FVector EnemyPos = FVector((*EnemyIt)->GetActorLocation().X - SPCharacter->GetActorLocation().X, (*EnemyIt)->GetActorLocation().Y - SPCharacter->GetActorLocation().Y, 0.f);

			EnemyPos = FQuat(FVector::UpVector, FMath::DegreesToRadians(-SPCharacter->GetActorRotation().Yaw - 90.f)) * EnemyPos;
			EnemyPosList.Add(FVector2D(EnemyPos.X, EnemyPos.Y));

			EnemyLockList.Add((*EnemyIt)->IsLockPlayer());
			EnemyRotateList.Add((*EnemyIt)->GetActorRotation().Yaw - SPCharacter->GetActorRotation().Yaw);		// 相对于玩家的Yaw方向
		}

		//每帧更新小地图的方向文字位置
		UpdateMapData.ExecuteIfBound(SPCharacter->GetActorRotation(), MiniMapCamera->GetMapSize(), &EnemyPosList, &EnemyLockList, &EnemyRotateList);
		/**
		 * @brief 委托接受GameMode传过来的玩家旋转,绑定的委托是GameMode的UpdateMapDirection
		 * @param PlayerRotator			玩家的旋转
		 * @param MiniMapSize			小地图的大小
		 * @param EnemyPosList			敌人的位置 2D
		 * @param EnemyLockList			敌人是否已经锁定了玩家
		 * @param EnemyRotateList		敌人的旋转
		 */
	}
}

void ADemoGameMode::LoadRecord()
{
	// 如果 RecordName 为空,直接 renturn。 如果是 Default,表明不需要加载存档
	if (DemoDataHandle::Get()->RecordName.IsEmpty() || DemoDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	// 循环检测存档是否已经存在
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It) 
	{
		//如果有一个一样就直接设置为true,并且直接跳出循环
		if ((*It).Equals(DemoDataHandle::Get()->RecordName))		// Equals 字符串对比，如果相同则返回 true
		{
			IsNeedLoadRecord = true;
			break;
		}
	}

	// 如果需要加载 并且 存档存在,进行加载
	if (IsNeedLoadRecord && UGameplayStatics::DoesSaveGameExist(DemoDataHandle::Get()->RecordName, 0))			// DoesSaveGameExist 查看是否存在具有指定名称的存档
	{
		GameRecord = Cast<UDemoSaveGame>(UGameplayStatics::LoadGameFromSlot(DemoDataHandle::Get()->RecordName, 0));		// LoadGameFromSlot 从给定名称加载存档
	}
	else
	{
		IsNeedLoadRecord = false;
	}

	//如果需要加载并且存档存在
	if (IsNeedLoadRecord && GameRecord)
	{
		//设置玩家位置和血量
		SPCharacter->SetActorLocation(GameRecord->PlayerLocation);
		SPState->LoadState(GameRecord->PlayerHP, GameRecord->PlayerHunger);

		//循环设置敌人
		int EnemyCount = 0;
		for (TActorIterator<ADemoEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt) 
		{
			if (EnemyCount < GameRecord->EnemyLoaction.Num())
			{
				(*EnemyIt)->SetActorLocation(GameRecord->EnemyLoaction[EnemyCount]);
				(*EnemyIt)->LoadHP(GameRecord->EnemyHP[EnemyCount]);
			}
			else 
			{
				//告诉这个敌人下一帧销毁
				(*EnemyIt)->IsDestroyNextTick = true;
			}
			++EnemyCount;
		}

		//循环设置岩石
		int RockCount = 0;
		for (TActorIterator<ADemoResourceRock> RockIt(GetWorld()); RockIt; ++RockIt) 
		{
			if (RockCount < GameRecord->ResourceRock.Num()) 
			{
				(*RockIt)->SetActorLocation(GameRecord->ResourceRock[RockCount]);
			}
			else 
			{
				//告诉这个资源下一帧销毁
				(*RockIt)->IsDestroyNextTick = true;
			}
			++RockCount;
		}

		//循环设置树木
		int TreeCount = 0;
		for (TActorIterator<ADemoResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) 
		{
			if (TreeCount < GameRecord->ResourceTree.Num()) 
			{
				(*TreeIt)->SetActorLocation(GameRecord->ResourceTree[TreeCount]);
			}
			else 
			{
				//告诉这个资源下一帧销毁
				(*TreeIt)->IsDestroyNextTick = true;
			}
			++TreeCount;
		}

		//循环设置拾取物品石头
		int StoneCount = 0;
		for (TActorIterator<ADemoPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) 
		{
			if (StoneCount < GameRecord->PickupStone.Num()) 
			{
				(*StoneIt)->SetActorLocation(GameRecord->PickupStone[StoneCount]);
			}
			else 
			{
				//告诉这个资源下一帧销毁
				(*StoneIt)->IsDestroyNextTick = true;
			}
			++StoneCount;
		}

		//循环设置拾取物品木头
		int WoodCount = 0;
		for (TActorIterator<ADemoPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) 
		{
			if (WoodCount < GameRecord->PickupWood.Num()) 
			{
				(*WoodIt)->SetActorLocation(GameRecord->PickupWood[WoodCount]);
			}
			else 
			{
				//告诉这个资源下一帧销毁
				(*WoodIt)->IsDestroyNextTick = true;
			}
			++WoodCount;
		}
	}
}

void ADemoGameMode::LoadRecordPackage()
{
	//如果背包没有初始化 或者 不用加载存档,直接返回
	if (!IsInitPackage || !IsNeedLoadRecord) return;

	if (IsNeedLoadRecord && GameRecord)
	{
		DemoPackageManager::Get()->LoadRecord(&GameRecord->InputIndex, &GameRecord->InputNum, &GameRecord->NormalIndex, &GameRecord->NormalNum, &GameRecord->ShortcutIndex, &GameRecord->ShortcutNum);
	}
	//最后设置不用加载存档了
	IsNeedLoadRecord = false;
}
