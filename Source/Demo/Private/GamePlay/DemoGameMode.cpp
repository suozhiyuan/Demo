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
	//������tick����
	PrimaryActorTick.bCanEverTick = true;

	//������
	HUDClass = ADemoGameHUD::StaticClass();
	PlayerControllerClass = ADemoPlayerController::StaticClass();
	PlayerStateClass = ADemoPlayerState::StaticClass();
	DefaultPawnClass = ADemoPlayerCharacter::StaticClass();

	//��ʼû�г�ʼ������
	IsInitPackage = false;

	//С��ͼ��û����
	IsCreateMiniMap = false;

	//��ʼ���ò���Ҫ���ش浵
	IsNeedLoadRecord = false;
}

void ADemoGameMode::Tick(float DeltaSeconds)
{
	//��ʼ�������С��ͼ�����
	InitializeMiniMapCamera();

	//���������ش浵, �ڶ�֡��ִ��
	LoadRecordPackage();

	//��ʼ������
	InitializePackage();
}

void ADemoGameMode::InitGamePlayModule()
{
	//�������
	SPController = Cast<ADemoPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPCharacter = Cast<ADemoPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SPState = Cast<ADemoPlayerState>(SPController->PlayerState);
}

void ADemoGameMode::SaveGame()
{
	//����浵����Default,�����б���
	if (DemoDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	//����һ���µĴ浵
	UDemoSaveGame* NewRecord = Cast<UDemoSaveGame>(UGameplayStatics::CreateSaveGameObject(UDemoSaveGame::StaticClass()));

	//�Դ浵���и�ֵ
	//�������λ�ú�Ѫ��
	NewRecord->PlayerLocation = SPCharacter->GetActorLocation();
	SPState->SaveState(NewRecord->PlayerHP, NewRecord->PlayerHunger);

	//ѭ�����õ���
	for (TActorIterator<ADemoEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
	{
		NewRecord->EnemyLoaction.Add((*EnemyIt)->GetActorLocation());
		NewRecord->EnemyHP.Add((*EnemyIt)->GetHP());
	}

	//ѭ��������ʯ
	for (TActorIterator<ADemoResourceRock> RockIt(GetWorld()); RockIt; ++RockIt)
	{
		NewRecord->ResourceRock.Add((*RockIt)->GetActorLocation());
	}

	//ѭ��������ľ
	for (TActorIterator<ADemoResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt)
	{
		NewRecord->ResourceTree.Add((*TreeIt)->GetActorLocation());
	}

	//ѭ������ʰȡ��Ʒʯͷ
	for (TActorIterator<ADemoPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) 
	{
		NewRecord->PickupStone.Add((*StoneIt)->GetActorLocation());
	}

	//ѭ������ʰȡ��Ʒľͷ
	for (TActorIterator<ADemoPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt)
	{
		NewRecord->PickupWood.Add((*WoodIt)->GetActorLocation());
	}

	//��ȡ��������
	DemoPackageManager::Get()->SaveData(NewRecord->InputIndex, NewRecord->InputNum, NewRecord->NormalIndex, NewRecord->NormalNum, NewRecord->ShortcutIndex, NewRecord->ShortcutNum);

	//�鿴�Ƿ��Ѿ��д浵����
	if (UGameplayStatics::DoesSaveGameExist(DemoDataHandle::Get()->RecordName, 0)) 
	{
		//�еĻ���ɾ��
		UGameplayStatics::DeleteGameInSlot(DemoDataHandle::Get()->RecordName, 0);
	}
	//����浵
	UGameplayStatics::SaveGameToSlot(NewRecord, DemoDataHandle::Get()->RecordName, 0);

	//�鿴json�Ƿ��Ѿ�������浵
	bool IsRecordExist = false;
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It)
	{
		//ֻҪ��һ����ͬ,������
		if ((*It).Equals(DemoDataHandle::Get()->RecordName)) 
		{
			IsRecordExist = true;
			break;
		}
	}
	//����浵������,�����ݹ�������Ӵ浵��json
	if (!IsRecordExist) DemoDataHandle::Get()->AddNewRecord();
}


void ADemoGameMode::BeginPlay()
{
	// ���Դ��룬DataHandle �� GameInstance ͬ�����п糡���������ݵĹ���
	DemoHelper::Debug(FString("DataHandle : ") + DemoDataHandle::Get()->RecordName, 30.f);
	DemoHelper::Debug(FString("GameInstance : ") + Cast<UDemoGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName, 30.f);

	// ��ʼ����Ϸ����
	//DemoDataHandle::Get()->InitializeGameData();

	if (!SPController) InitGamePlayModule();

	//���ű�������
	USoundWave* BGMusic = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Res/Sound/GameSound/GameBG.GameBG'"));		// ����������Դ
	BGMusic->bLooping = true;																										// �����Ƿ�ѭ��
	UGameplayStatics::PlaySound2D(GetWorld(), BGMusic, 0.1f);															// ���ţ�����3Ϊ��ʼ������Ĭ��ֵ��1

	LoadRecord();
}

void ADemoGameMode::InitializePackage()
{
	if (IsInitPackage) return;

	//��PackageWidget��ʼ������������
	InitPackageManager.ExecuteIfBound();

	//�󶨶�����Ʒί��
	DemoPackageManager::Get()->PlayerThrowObject.BindUObject(SPCharacter, &ADemoPlayerCharacter::PlayerThrowObject);
	//���޸Ŀ������Ϣί��
	DemoPackageManager::Get()->ChangeHandObject.BindUObject(SPState, &ADemoPlayerState::ChangeHandObject);

	IsInitPackage = true;
}

void ADemoGameMode::InitializeMiniMapCamera()
{
	//�����ͼ��������������� ���� �����Ѿ�����
	if (!IsCreateMiniMap && GetWorld())
	{
		//����С��ͼ�����
		MiniMapCamera = GetWorld()->SpawnActor<ADemoSceneCapture2D>(ADemoSceneCapture2D::StaticClass());

		// ��������������Ϸʱ�����
		//����ί�и� MiniMapWidget ������Ⱦ�� MiniMapTex
		//RegisterMiniMap.ExecuteIfBound(MiniMapCamera->GetMiniMapTex());

		//���޸�С��ͼ��Ұ��ί��
		SPController->UpdateMiniMapWidth.BindUObject(MiniMapCamera, &ADemoSceneCapture2D::UpdateMiniMapWidth);

		//�����Ѿ�����С��ͼ
		IsCreateMiniMap = true;
	}

	//���С��ͼ�Ѿ�����
	if (IsCreateMiniMap)
	{
		//ÿ֡����С��ͼ�������λ�ú���ת
		MiniMapCamera->UpdateTransform(SPCharacter->GetActorLocation(), SPCharacter->GetActorRotation());

		TArray<FVector2D> EnemyPosList;		// ����λ��
		TArray<bool> EnemyLockList;			// �Ƿ�����
		TArray<float> EnemyRotateList;		// ������ת

		//��ȡ�����еĵ���
		for (TActorIterator<ADemoEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
		{
			// �������λ��
			FVector EnemyPos = FVector((*EnemyIt)->GetActorLocation().X - SPCharacter->GetActorLocation().X, (*EnemyIt)->GetActorLocation().Y - SPCharacter->GetActorLocation().Y, 0.f);

			EnemyPos = FQuat(FVector::UpVector, FMath::DegreesToRadians(-SPCharacter->GetActorRotation().Yaw - 90.f)) * EnemyPos;
			EnemyPosList.Add(FVector2D(EnemyPos.X, EnemyPos.Y));

			EnemyLockList.Add((*EnemyIt)->IsLockPlayer());
			EnemyRotateList.Add((*EnemyIt)->GetActorRotation().Yaw - SPCharacter->GetActorRotation().Yaw);		// �������ҵ�Yaw����
		}

		//ÿ֡����С��ͼ�ķ�������λ��
		UpdateMapData.ExecuteIfBound(SPCharacter->GetActorRotation(), MiniMapCamera->GetMapSize(), &EnemyPosList, &EnemyLockList, &EnemyRotateList);
		/**
		 * @brief ί�н���GameMode�������������ת,�󶨵�ί����GameMode��UpdateMapDirection
		 * @param PlayerRotator			��ҵ���ת
		 * @param MiniMapSize			С��ͼ�Ĵ�С
		 * @param EnemyPosList			���˵�λ�� 2D
		 * @param EnemyLockList			�����Ƿ��Ѿ����������
		 * @param EnemyRotateList		���˵���ת
		 */
	}
}

void ADemoGameMode::LoadRecord()
{
	// ��� RecordName Ϊ��,ֱ�� renturn�� ����� Default,��������Ҫ���ش浵
	if (DemoDataHandle::Get()->RecordName.IsEmpty() || DemoDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	// ѭ�����浵�Ƿ��Ѿ�����
	for (TArray<FString>::TIterator It(DemoDataHandle::Get()->RecordDataList); It; ++It) 
	{
		//�����һ��һ����ֱ������Ϊtrue,����ֱ������ѭ��
		if ((*It).Equals(DemoDataHandle::Get()->RecordName))		// Equals �ַ����Աȣ������ͬ�򷵻� true
		{
			IsNeedLoadRecord = true;
			break;
		}
	}

	// �����Ҫ���� ���� �浵����,���м���
	if (IsNeedLoadRecord && UGameplayStatics::DoesSaveGameExist(DemoDataHandle::Get()->RecordName, 0))			// DoesSaveGameExist �鿴�Ƿ���ھ���ָ�����ƵĴ浵
	{
		GameRecord = Cast<UDemoSaveGame>(UGameplayStatics::LoadGameFromSlot(DemoDataHandle::Get()->RecordName, 0));		// LoadGameFromSlot �Ӹ������Ƽ��ش浵
	}
	else
	{
		IsNeedLoadRecord = false;
	}

	//�����Ҫ���ز��Ҵ浵����
	if (IsNeedLoadRecord && GameRecord)
	{
		//�������λ�ú�Ѫ��
		SPCharacter->SetActorLocation(GameRecord->PlayerLocation);
		SPState->LoadState(GameRecord->PlayerHP, GameRecord->PlayerHunger);

		//ѭ�����õ���
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
				//�������������һ֡����
				(*EnemyIt)->IsDestroyNextTick = true;
			}
			++EnemyCount;
		}

		//ѭ��������ʯ
		int RockCount = 0;
		for (TActorIterator<ADemoResourceRock> RockIt(GetWorld()); RockIt; ++RockIt) 
		{
			if (RockCount < GameRecord->ResourceRock.Num()) 
			{
				(*RockIt)->SetActorLocation(GameRecord->ResourceRock[RockCount]);
			}
			else 
			{
				//���������Դ��һ֡����
				(*RockIt)->IsDestroyNextTick = true;
			}
			++RockCount;
		}

		//ѭ��������ľ
		int TreeCount = 0;
		for (TActorIterator<ADemoResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) 
		{
			if (TreeCount < GameRecord->ResourceTree.Num()) 
			{
				(*TreeIt)->SetActorLocation(GameRecord->ResourceTree[TreeCount]);
			}
			else 
			{
				//���������Դ��һ֡����
				(*TreeIt)->IsDestroyNextTick = true;
			}
			++TreeCount;
		}

		//ѭ������ʰȡ��Ʒʯͷ
		int StoneCount = 0;
		for (TActorIterator<ADemoPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) 
		{
			if (StoneCount < GameRecord->PickupStone.Num()) 
			{
				(*StoneIt)->SetActorLocation(GameRecord->PickupStone[StoneCount]);
			}
			else 
			{
				//���������Դ��һ֡����
				(*StoneIt)->IsDestroyNextTick = true;
			}
			++StoneCount;
		}

		//ѭ������ʰȡ��Ʒľͷ
		int WoodCount = 0;
		for (TActorIterator<ADemoPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) 
		{
			if (WoodCount < GameRecord->PickupWood.Num()) 
			{
				(*WoodIt)->SetActorLocation(GameRecord->PickupWood[WoodCount]);
			}
			else 
			{
				//���������Դ��һ֡����
				(*WoodIt)->IsDestroyNextTick = true;
			}
			++WoodCount;
		}
	}
}

void ADemoGameMode::LoadRecordPackage()
{
	//�������û�г�ʼ�� ���� ���ü��ش浵,ֱ�ӷ���
	if (!IsInitPackage || !IsNeedLoadRecord) return;

	if (IsNeedLoadRecord && GameRecord)
	{
		DemoPackageManager::Get()->LoadRecord(&GameRecord->InputIndex, &GameRecord->InputNum, &GameRecord->NormalIndex, &GameRecord->NormalNum, &GameRecord->ShortcutIndex, &GameRecord->ShortcutNum);
	}
	//������ò��ü��ش浵��
	IsNeedLoadRecord = false;
}
