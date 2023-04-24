// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DemoEnemyController.generated.h"

/**
 *
 */
UCLASS()
class DEMO_API ADemoEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	ADemoEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	virtual void Tick(float DeltaTime) override;

	//��ȡ��ҵ�λ��
	FVector GetPlayerLocation() const;

	//����Ƿ��Ѿ�����
	bool IsPlayerDead();

	//���������,��Character��OnSeePlayer����
	void OnSeePlayer();

	//��ʧ��Ҷ�λ
	void LoosePlayer();

	//�ж�����Ƿ���Զ��
	bool IsPlayerAway();

	//��ȡ���ָ��
	UObject* GetPlayerPawn();

	//���߿������������
	void ResetProcess(bool IsFinish);

	//�����˺�,����ʣ������ֵ
	void UpdateDamageRatio(float HPRatioVal);

	//����˺�״̬
	void FinishStateHurt();

	//��ɷ���״̬
	void FinishStateDefence();

	//����
	void EnemyDead();

public:

	//�Ƿ����������
	bool IsLockPlayer;


protected:

	virtual void BeginPlay() override;


private:

	//����״̬����
	void UpdateStatePama();

private:
	//��ҵ�ָ��
	class ADemoPlayerCharacter* SPCharacter;

	//���˽�ɫָ��
	class ADemoEnemyCharacter* SECharacter;

	// �ڰ��������
	class UBlackboardComponent* BlackboardComp;

	// ��Ϊ�����
	class UBehaviorTreeComponent* BehaviorComp;

	//��������ҵľ�������,����6��,ÿ�������һ��
	TArray<float> EPDisList;

	//ʱ��ί�о����ÿ0.3������Ϸ�����
	FTimerHandle EPDisHandle;

	//Ѫֵ
	float HPRatio;

	//�Ƿ�����������״̬
	bool IsAllowHurt;

	//���˼�ʱ��
	float HurtTimeCount;
};
