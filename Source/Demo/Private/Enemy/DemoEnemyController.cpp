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

// 开始控制，会在BeginPlay之前执行 
void ADemoEnemyController::OnPossess(APawn* InPawn)
{
	//绝对一定必须要调用父类函数
	Super::OnPossess(InPawn);

	//顺便在这里实例化一下角色
	SECharacter = Cast<ADemoEnemyCharacter>(InPawn);

	// 获取行为树资源，这样做会有个问题，1个敌人时行为树有用，多个敌人便会有行为树不生效的问题
	UBehaviorTree* StaticBehaviorTreeObject = LoadObject<UBehaviorTree>(NULL, TEXT("BehaviorTree'/Game/Blueprint/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));
	// 由于创建多个单位后上方的行为树不在生效，所以这里做了一个复制对象的方法lAi规避该问题
	UBehaviorTree* BehaviorTreeObject = DuplicateObject<UBehaviorTree>(StaticBehaviorTreeObject, NULL);

	//如果资源不存在,直接返回
	if (!BehaviorTreeObject) return;

	// 复制黑板数据资源
	BehaviorTreeObject->BlackboardAsset = DuplicateObject<UDemoEnemyBlackboardData>((UDemoEnemyBlackboardData*)StaticBehaviorTreeObject->BlackboardAsset, NULL);

	BlackboardComp = Blackboard;		// 将父类的黑板赋值给当前黑板数据
	bool IsSuccess = true;				// 加载黑板数据是否成功

	// BlackboardAsset 存在，Blackboard为空或者与BlackboardAsset不匹配
	if (BehaviorTreeObject->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTreeObject->BlackboardAsset) == false))
	{
		IsSuccess = UseBlackboard(BehaviorTreeObject->BlackboardAsset, BlackboardComp);
	}

	// 绑定行为树组件
	if (IsSuccess)
	{
		BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);									// BrainComponent 负责行为的组件
		if (!BehaviorComp)
		{
			BehaviorComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));		// 如果转化没有成功则实例化一下
			BehaviorComp->RegisterComponent();															// 注册一下
		}
		BrainComponent = BehaviorComp;										
		check(BehaviorComp != NULL);																	// 判断是否为空，为空直接跳出

		BehaviorComp->StartTree(*BehaviorTreeObject, EBTExecutionMode::Looped);						// 启动行为树

		// 以上代码来自于
		//RunBehaviorTree(BehaviorTreeObject);

		// 设置预状态为巡逻
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Patrol);			// 设置状态枚举

		//修改敌人的初始移动速度是100
		SECharacter->SetMaxSpeed(100.f);

		// 也是一种修改状态的方法
		///*int32 EnemyStateIndex = BlackboardComp->GetKeyID("EnemyState");
		//BlackboardComp->SetValue<UBlackboardKeyType_Enum>(EnemyStateIndex, (UBlackboardKeyType_Enum::FDataType)EEnemyAIState::ES_Patrol);*/
	}
}

void ADemoEnemyController::OnUnPossess()
{
	Super::OnUnPossess();

	//停止行为树
	if (BehaviorComp) BehaviorComp->StopTree();
}

void ADemoEnemyController::BeginPlay()
{
	//绝对一定必须要调用父类函数，否则C++调用行为树将没有效果
	Super::BeginPlay();

	//初始化一下玩家指针,这个指针会一直存在
	SPCharacter = Cast<ADemoPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));

	//如果角色没有初始化
	if (!SECharacter) SECharacter = Cast<ADemoEnemyCharacter>(GetPawn());

	//初始设定没有锁定玩家
	IsLockPlayer = false;

	//进行定时器委托绑定
	FTimerDelegate EPDisDele = FTimerDelegate::CreateUObject(this, &ADemoEnemyController::UpdateStatePama);
	GetWorld()->GetTimerManager().SetTimer(EPDisHandle, EPDisDele, 0.3f, true);		// 每0.3秒执行一次时间委托

	//血量百分比初始化为1
	HPRatio = 1;

	//设置状态计时器
	IsAllowHurt = false;
	HurtTimeCount = 0.f;
}


void ADemoEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//如果玩家指针和角色指针存在
	if (SECharacter && SPCharacter) SECharacter->UpdateHPBarRotation(SPCharacter->GetCameraPos());
}

FVector ADemoEnemyController::GetPlayerLocation() const
{
	//如果玩家指针存在,返回玩家位置
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
	//如果已经锁定了玩家或者玩家已经死了,不再执行下面的函数
	if (IsLockPlayer || IsPlayerDead()) return;

	//设置锁定了玩家
	IsLockPlayer = true;

	//修改预状态为追逐
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);

	//修改最大速度为300
	SECharacter->SetMaxSpeed(300.f);
}

void ADemoEnemyController::LoosePlayer()
{
	//设置丢失玩家的锁定
	IsLockPlayer = false;
}

//判定玩家是否在远离
bool ADemoEnemyController::IsPlayerAway()
{
	// 如果目标锁定，或没有玩家角色，或目标数量小于6，或玩家角色死亡，表示玩家没有远离
	if (!IsLockPlayer || !SPCharacter || EPDisList.Num() < 6 || IsPlayerDead()) return false;

	int BiggerNum = 0;
	float LastDis = -1.f;

	//只要有三个比前面的大,就判定远离了
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
	//修改完成状态
	BlackboardComp->SetValueAsBool("ProcessFinish", IsFinish);
}

void ADemoEnemyController::UpdateDamageRatio(float HPRatioVal)
{
	//更新血值百分比
	HPRatio = HPRatioVal;

	//状态修改为受伤
	if (IsAllowHurt) BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Hurt);

	//设置允许受伤状态
	IsAllowHurt = false;
}

void ADemoEnemyController::FinishStateHurt()
{
	//如果没有锁定玩家,设置锁定
	if (!IsLockPlayer) IsLockPlayer = true;

	//如果血值在0.2f以下
	if (HPRatio < 0.2f)
	{
		//创建随机流
		FRandomStream Stream;
		//产生新的随机种子
		Stream.GenerateNewSeed();
		//先随机一个动作类别
		int ActionRatio = Stream.RandRange(0, 10);

		// 30的几率触发防御
		if (ActionRatio < 4) 
		{
			// 先进入防御状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			// 进入逃跑状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
	}
	else
	{
		//创建随机流
		FRandomStream Stream;
		//产生新的随机种子
		Stream.GenerateNewSeed();
		//先随机一个动作类别
		int ActionRatio = Stream.RandRange(0, 10);

		//30的几率触发防御
		if (ActionRatio < 4) 
		{
			//进入防御状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			//进入攻击
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void ADemoEnemyController::FinishStateDefence()
{
	//设置状态完成
	ResetProcess(true);

	//停止防御动作
	SECharacter->StopDefence();

	//获取与玩家的距离
	float SEToSP = FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation());

	//如果玩家还在攻击并且距离小于200,继续防御状态
	if (SPCharacter->IsAttack && SEToSP < 200.f)
	{
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
	}
	else
	{
		//如果血值小于0.2,逃跑
		if (HPRatio < 0.2f)
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
		else
		{
			//跳到攻击状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void ADemoEnemyController::EnemyDead()
{
	//停止行为树
	if (BehaviorComp) BehaviorComp->StopTree(EBTStopMode::Safe);

	////临时代码,注销时间函数
	//if (EPDisHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(EPDisHandle);
}

void ADemoEnemyController::UpdateStatePama()
{
	//更新与玩家的距离序列
	if (EPDisList.Num() < 6)
	{
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}
	else
	{
		EPDisList.RemoveAt(0);		// 最前边的移除
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}

	//更新受伤害序列,受伤一次后6秒内不允许进入受伤状态
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
