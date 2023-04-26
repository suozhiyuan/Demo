// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DemoType.h"
#include "GameFramework/PlayerController.h"
#include "DemoPlayerController.generated.h"


//�޸�׼��ί��
DECLARE_DELEGATE_TwoParams(FUpdatePointer, bool, float)
//��ʾUIί��
DECLARE_DELEGATE_TwoParams(FShowGameUI, EGameUIType::Type, EGameUIType::Type)
//�޸�С��ͼ��Ұ��Χί��
DECLARE_DELEGATE_OneParam(FUpdateMiniMapWidth, int)

/**
 *
 */
UCLASS()
class DEMO_API ADemoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ADemoPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	// �������
	virtual void SetupInputComponent() override;

	//�� Character ���ֳ���Ʒ���и���,��������� playerstate �ڻ����
	void ChangeHandObject();

	//����
	void PlayerDead();

public:

	//��ȡ��ҽ�ɫ
	class ADemoPlayerCharacter* SPCharacter;
	class ADemoPlayerState* SPState;


	//ʵʱ�޸�׼�ǵ�ί��,ע��ĺ�����PointerWidget��UpdatePointer
	FUpdatePointer UpdatePointer;

	//��ʾ��ϷUI����ί��,�󶨵ķ�����GameHUDWidget��ShowGameUI
	FShowGameUI ShowGameUI;

	//�޸�С��ͼ��Ұ��Χί��,ע�ắ����DemoSceneCapture2D��UpdateMiniMapWidth 
	FUpdateMiniMapWidth UpdateMiniMapWidth;

protected:

	virtual void BeginPlay() override;

private:

	//�л��ӽ�
	void ChangeView();

	//��갴���¼�
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();

	//�������¹����¼�
	void ScrollUpEvent();
	void ScrollDownEvent();

	//�޸�Ԥ����
	void ChangePreUpperType(EUpperBody::Type RightType);

	//���߼����
	FHitResult RayGetHitResult(FVector TraceStart, FVector TraceEnd);

	//���߻���
	void DrawRayLine(FVector StartPos, FVector EndPos, float Duration);

	//�������߼��
	void RunRayCast();

	//��Ϊ״̬��
	void StateMachine();

	//ESC�����¼�
	void EscEvent();

	//E������
	void PackageEvent();

	//T��������
	void ChatRoomEvent();

	//ת������ģʽ,trueΪ��Ϸģʽ,falseΪ���ģʽ
	void SwitchInputMode(bool IsGameOnly);

	//������ס����
	void LockedInput(bool IsLocked);

	//С��ͼ�����¼�
	void AddMapSizeStart();
	void AddMapSizeStop();
	void ReduceMapSizeStart();
	void ReduceMapSizeStop();

	//��Tick��������С��ͼ�¼�
	void TickMiniMap();

	//����ʱ�亯��
	void DeadTimeOut();


private:

	//���Ԥ����
	EUpperBody::Type LeftUpperType;

	//�Ҽ�Ԥ����
	EUpperBody::Type RightUpperType;

	//�Ƿ�ס��������
	bool IsLeftButtonDown;
	bool IsRightButtonDown;

	//��⵽����Դ
	AActor* RayActor;

	//���浱ǰUI״̬
	EGameUIType::Type CurrentUIType;

	//С��ͼ����״̬
	EMiniMapSizeMode::Type MiniMapSizeMode;

	//����ʱ��ί��
	FTimerHandle DeadHandle;
};
