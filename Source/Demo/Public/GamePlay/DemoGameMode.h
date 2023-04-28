// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoGameMode.generated.h"


//��ʼ������������ί��
DECLARE_DELEGATE(FInitPackageManager)

//ע��MiniMap����ͼ�Ͳ���
DECLARE_DELEGATE_OneParam(FRegisterMiniMap, class UTextureRenderTarget2D*)

//����MiniMap������
DECLARE_DELEGATE_FiveParams(FUpdateMapData, const FRotator, const float, const TArray<FVector2D>*, const TArray<bool>*, const TArray<float>*)

/**
 *
 */
UCLASS()
class DEMO_API ADemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ADemoGameMode();

	//��д֡����
	virtual void Tick(float DeltaSeconds) override;

	//�����ֵ,��GameHUD����,����������������
	void InitGamePlayModule();

	// ������Ϸ
	void SaveGame();

public:
	class ADemoPlayerController* SPController;

	class ADemoPlayerCharacter* SPCharacter;

	class ADemoPlayerState* SPState;

	//��ʼ����������ί��,�󶨵ķ�����PackageWidget��InitPackageManager����
	FInitPackageManager InitPackageManager;

	//����ί��,�󶨵ķ����� MiniMapWidget �� RegisterMiniMap
	FRegisterMiniMap RegisterMiniMap;

	//����ί��,���ڸ���С��ͼ�ķ�������λ��,�󶨵ķ�����MiniMapWidget��UpdateMapDirection
	FUpdateMapData UpdateMapData;


protected:
	virtual void BeginPlay() override;

	//��ʼ������������
	void InitializePackage();

	//��ʼ�������С��ͼ�����
	void InitializeMiniMapCamera();

	//�浵����
	void LoadRecord();

	//���������м��ش浵,�������һ��Ҫ�ڵڶ�֡��ִ��,��������û��ʼ����ɻ����
	void LoadRecordPackage();

private:
	//�Ƿ��Ѿ���ʼ������
	bool IsInitPackage;

	//�Ƿ��Ѿ�����С��ͼ�����
	bool IsCreateMiniMap;

	//С��ͼ���ָ��
	class ADemoSceneCapture2D* MiniMapCamera;

	//�Ƿ���Ҫ���ش浵
	bool IsNeedLoadRecord;

	//��Ϸ�浵ָ��
	class UDemoSaveGame* GameRecord;

};
