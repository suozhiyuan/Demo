// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DemoEnemyController.h"

#include "AI/DemoEnemyBlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/DemoEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DemoPlayerCharacter.h"


ADemoEnemyController::ADemoEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

// ��ʼ���ƣ�����BeginPlay֮ǰִ�� 
void ADemoEnemyController::OnPossess(APawn* InPawn)
{
	//����һ������Ҫ���ø��ຯ��
	Super::OnPossess(InPawn);

	//˳��������ʵ����һ�½�ɫ
	SECharacter = Cast<ADemoEnemyCharacter>(InPawn);

	// ��ȡ��Ϊ����Դ�����������и����⣬1������ʱ��Ϊ�����ã�������˱������Ϊ������Ч������
	UBehaviorTree* StaticBehaviorTreeObject = LoadObject<UBehaviorTree>(NULL, TEXT("BehaviorTree'/Game/Blueprint/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));
	// ���ڴ��������λ���Ϸ�����Ϊ��������Ч��������������һ�����ƶ���ķ���lAi��ܸ�����
	UBehaviorTree* BehaviorTreeObject = DuplicateObject<UBehaviorTree>(StaticBehaviorTreeObject, NULL);

	//�����Դ������,ֱ�ӷ���
	if (!BehaviorTreeObject) return;

	// ���ƺڰ�������Դ
	BehaviorTreeObject->BlackboardAsset = DuplicateObject<UDemoEnemyBlackboardData>((UDemoEnemyBlackboardData*)StaticBehaviorTreeObject->BlackboardAsset, NULL);

	BlackboardComp = Blackboard;		// ������ĺڰ帳ֵ����ǰ�ڰ�����
	bool IsSuccess = true;				// ���غڰ������Ƿ�ɹ�

	// BlackboardAsset ���ڣ�BlackboardΪ�ջ�����BlackboardAsset��ƥ��
	if (BehaviorTreeObject->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTreeObject->BlackboardAsset) == false))
	{
		IsSuccess = UseBlackboard(BehaviorTreeObject->BlackboardAsset, BlackboardComp);
	}

	// ����Ϊ�����
	if (IsSuccess)
	{
		BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);									// BrainComponent ������Ϊ�����
		if (!BehaviorComp)
		{
			BehaviorComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));		// ���ת��û�гɹ���ʵ����һ��
			BehaviorComp->RegisterComponent();															// ע��һ��
		}
		BrainComponent = BehaviorComp;										
		check(BehaviorComp != NULL);																	// �ж��Ƿ�Ϊ�գ�Ϊ��ֱ������

		BehaviorComp->StartTree(*BehaviorTreeObject, EBTExecutionMode::Looped);						// ������Ϊ��

		// ���ϴ���������
		//RunBehaviorTree(BehaviorTreeObject);

		// ����Ԥ״̬ΪѲ��
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Patrol);			// ����״̬ö��

		//�޸ĵ��˵ĳ�ʼ�ƶ��ٶ���100
		SECharacter->SetMaxSpeed(100.f);

		// Ҳ��һ���޸�״̬�ķ���
		///*int32 EnemyStateIndex = BlackboardComp->GetKeyID("EnemyState");
		//BlackboardComp->SetValue<UBlackboardKeyType_Enum>(EnemyStateIndex, (UBlackboardKeyType_Enum::FDataType)EEnemyAIState::ES_Patrol);*/
	}
}

void ADemoEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	//ֹͣ��Ϊ��
	if (BehaviorComp) BehaviorComp->StopTree();
}

void ADemoEnemyController::BeginPlay()
{
	//����һ������Ҫ���ø��ຯ��������C++������Ϊ����û��Ч��
	Super::BeginPlay();

	//��ʼ��һ�����ָ��,���ָ���һֱ����
	SPCharacter = Cast<ADemoPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));

	//�����ɫû�г�ʼ��
	if (!SECharacter) SECharacter = Cast<ADemoEnemyCharacter>(GetPawn());

	//��ʼ�趨û���������
	IsLockPlayer = false;

	//���ж�ʱ��ί�а�
	FTimerDelegate EPDisDele = FTimerDelegate::CreateUObject(this, &ADemoEnemyController::UpdateStatePama);
	GetWorld()->GetTimerManager().SetTimer(EPDisHandle, EPDisDele, 0.3f, true);		// ÿ0.3��ִ��һ��ʱ��ί��

	//Ѫ���ٷֱȳ�ʼ��Ϊ1
	HPRatio = 1;

	//����״̬��ʱ��
	IsAllowHurt = false;
	HurtTimeCount = 0.f;
}


void ADemoEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������ָ��ͽ�ɫָ�����
	if (SECharacter && SPCharacter) SECharacter->UpdateHPBarRotation(SPCharacter->GetCameraPos());
}

FVector ADemoEnemyController::GetPlayerLocation() const
{
	//������ָ�����,�������λ��
	if (SPCharacter) return SPCharacter->GetActorLocation();
	return FVector::ZeroVector;
}

bool ADemoEnemyController::IsPlayerDead()
{
	if (SPCharacter) return SPCharacter->IsPlayerDead();
	return false;
}

void ADemoEnemyController::OnSeePlayer()
{
	//����Ѿ���������һ�������Ѿ�����,����ִ������ĺ���
	if (IsLockPlayer || IsPlayerDead()) return;

	//�������������
	IsLockPlayer = true;

	//�޸�Ԥ״̬Ϊ׷��
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);

	//�޸�����ٶ�Ϊ300
	SECharacter->SetMaxSpeed(300.f);
}

void ADemoEnemyController::LoosePlayer()
{
	//���ö�ʧ��ҵ�����
	IsLockPlayer = false;
}

//�ж�����Ƿ���Զ��
bool ADemoEnemyController::IsPlayerAway()
{
	// ���Ŀ����������û����ҽ�ɫ����Ŀ������С��6������ҽ�ɫ��������ʾ���û��Զ��
	if (!IsLockPlayer || !SPCharacter || EPDisList.Num() < 6 || IsPlayerDead()) return false;

	int BiggerNum = 0;
	float LastDis = -1.f;

	//ֻҪ��������ǰ��Ĵ�,���ж�Զ����
	for (TArray<float>::TIterator It(EPDisList); It; ++It)
	{
		if (*It > LastDis) BiggerNum += 1;
		LastDis = *It;
	}
	return BiggerNum > 3;
}

UObject* ADemoEnemyController::GetPlayerPawn()
{
	return SPCharacter;
}

void ADemoEnemyController::ResetProcess(bool IsFinish)
{
	//�޸����״̬
	BlackboardComp->SetValueAsBool("ProcessFinish", IsFinish);
}

void ADemoEnemyController::UpdateDamageRatio(float HPRatioVal)
{
	//����Ѫֵ�ٷֱ�
	HPRatio = HPRatioVal;

	//״̬�޸�Ϊ����
	if (IsAllowHurt) BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Hurt);

	//������������״̬
	IsAllowHurt = false;
}

void ADemoEnemyController::FinishStateHurt()
{
	//���û���������,��������
	if (!IsLockPlayer) IsLockPlayer = true;

	//���Ѫֵ��0.2f����
	if (HPRatio < 0.2f)
	{
		//���������
		FRandomStream Stream;
		//�����µ��������
		Stream.GenerateNewSeed();
		//�����һ���������
		int ActionRatio = Stream.RandRange(0, 10);

		// 30�ļ��ʴ�������
		if (ActionRatio < 4) 
		{
			// �Ƚ������״̬
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			// ��������״̬
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
	}
	else
	{
		//���������
		FRandomStream Stream;
		//�����µ��������
		Stream.GenerateNewSeed();
		//�����һ���������
		int ActionRatio = Stream.RandRange(0, 10);

		//30�ļ��ʴ�������
		if (ActionRatio < 4) 
		{
			//�������״̬
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			//���빥��
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void ADemoEnemyController::FinishStateDefence()
{
	//����״̬���
	ResetProcess(true);

	//ֹͣ��������
	SECharacter->StopDefence();

	//��ȡ����ҵľ���
	float SEToSP = FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation());

	//�����һ��ڹ������Ҿ���С��200,��������״̬
	if (SPCharacter->IsAttack && SEToSP < 200.f)
	{
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
	}
	else
	{
		//���ѪֵС��0.2,����
		if (HPRatio < 0.2f)
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
		else
		{
			//��������״̬
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void ADemoEnemyController::EnemyDead()
{
	//ֹͣ��Ϊ��
	if (BehaviorComp) BehaviorComp->StopTree(EBTStopMode::Safe);

	////��ʱ����,ע��ʱ�亯��
	//if (EPDisHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(EPDisHandle);
}

void ADemoEnemyController::UpdateStatePama()
{
	//��������ҵľ�������
	if (EPDisList.Num() < 6)
	{
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}
	else
	{
		EPDisList.RemoveAt(0);		// ��ǰ�ߵ��Ƴ�
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}

	//�������˺�����,����һ�κ�6���ڲ������������״̬
	if (HurtTimeCount < 6.f)
	{
		HurtTimeCount += 0.3f;
	}
	else 
	{
		HurtTimeCount = 0.f;
		IsAllowHurt = true;
	}
}
