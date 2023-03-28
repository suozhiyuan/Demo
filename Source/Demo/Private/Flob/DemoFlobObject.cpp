// Fill out your copyright notice in the Description page of Project Settings.


#include "Flob/DemoFlobObject.h"

#include "Components/BoxComponent.h"
#include "Data/DemoDataHandle.h"
#include "Data/DemoType.h"

// Sets default values
ADemoFlobObject::ADemoFlobObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = (USceneComponent*)BoxCollision;

	//设置碰撞属性
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));

	//启动物体模拟，可以与世界中的其他物体产生碰撞结果
	BoxCollision->SetSimulatePhysics(true);

	//锁定旋转
	BoxCollision->SetConstraintMode(EDOFMode::Default);				// EDOFMode::Default 从项目设置中继承自由度。
	BoxCollision->GetBodyInstance()->bLockXRotation = true;
	BoxCollision->GetBodyInstance()->bLockYRotation = true;
	BoxCollision->GetBodyInstance()->bLockZRotation = true;

	//设置大小
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);			// 更改这个原始组件的整个ResponseToChannels容器
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);		// 控制此主体启用哪种类型的碰撞

	//设置变换
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	// 材质实例
	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));

	//动态创建材质
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);
}

// Called when the game starts or when spawned
void ADemoFlobObject::BeginPlay()
{
	Super::BeginPlay();

	////检测世界是否存在
	//if (!GetWorld()) return;

	////注册检测事件
	//FTimerDelegate DetectPlayerDele;
	//DetectPlayerDele.BindUObject(this, &ADemoFlobObject::DetectPlayer);
	////每秒运行一次,循环运行,延迟3秒运行
	//GetWorld()->GetTimerManager().SetTimer(DetectTimer, DetectPlayerDele, 1.f, true, 3.f);

	////注册销毁事件
	//FTimerDelegate DestroyDele;
	//DestroyDele.BindUObject(this, &ADemoFlobObject::DestroyEvent);
	//GetWorld()->GetTimerManager().SetTimer(DestroyTimer, DestroyDele, 30.f, false);

	////初始玩家指针为空
	//SPCharacter = NULL;
}

// Called every frame
void ADemoFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////一直旋转
	//BaseMesh->AddLocalRotation(FRotator(DeltaTime * 60.f, 0.f, 0.f));

	////如果检测到玩家
	//if (SPCharacter) {
	//	//靠近玩家
	//	SetActorLocation(FMath::VInterpTo(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f), DeltaTime, 5.f));
	//	//如果距离接近0
	//	if (FVector::Distance(GetActorLocation(), SPCharacter->GetActorLocation() + FVector(0.f, 0.f, 40.f)) < 10.f)
	//	{
	//		//判断玩家背包是否有空间
	//		if (SPCharacter->IsPackageFree(ObjectIndex)) {
	//			//添加对应的物品到背包
	//			SPCharacter->AddPackageObject(ObjectIndex);
	//			//销毁自己
	//			DestroyEvent();
	//		}
	//		else {
	//			//如果玩家背包不为空,重置参数
	//			SPCharacter = NULL;
	//			//唤醒检测
	//			GetWorld()->GetTimerManager().UnPauseTimer(DetectTimer);
	//			//唤醒销毁线程
	//			GetWorld()->GetTimerManager().UnPauseTimer(DestroyTimer);
	//			//开启物理模拟
	//			BoxCollision->SetSimulatePhysics(true);
	//		}
	//	}
	//}
}

void ADemoFlobObject::CreateFlobObject(int ObjectID)
{
	//指定ID
	ObjectIndex = ObjectID;

	//渲染贴图
	RenderTexture();

	//做随机方向的力
	FRandomStream Stream;
	Stream.GenerateNewSeed();											// 产生随机种子
	int DirYaw = Stream.RandRange(-180, 180);					// 从一个范围内随机一个角度
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);			// 将随机值传入到 Yaw

	//添加力
	BoxCollision->AddForce((FVector(0.f, 0.f, 4.f) + ForceRot.Vector()) * 100000.f);
}


//void ADemoFlobObject::ThrowFlobObject(int ObjectID, float DirYaw)
//{
//	//指定ID
//	ObjectIndex = ObjectID;
//
//	//渲染贴图
//	RenderTexture();
//
//	//随机方向添加力
//	FRandomStream Stream;
//
//	//产生新的随机种子
//	Stream.GenerateNewSeed();
//
//	//添加偏移方向
//	DirYaw += Stream.RandRange(-30, 30);
//
//	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);
//
//	//添加力
//	BoxCollision->AddForce((FVector(0.f, 0.f, 2.f) + ForceRot.Vector()) * 120000.f);
//}

void ADemoFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *DemoDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);							// 贴图路径
	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);					// 贴图给到动态材质
	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}

//void ADemoFlobObject::DetectPlayer()
//{
//	//检测世界是否存在
//	if (!GetWorld()) return;
//
//	//保存检测结果
//	TArray<FOverlapResult> Overlaps;
//	FCollisionObjectQueryParams ObjectParams;
//	FCollisionQueryParams Params;
//	Params.AddIgnoredActor(this);
//	Params.bTraceAsyncScene = true;
//
//	//进行动态检测,检测范围是200,检测成功的话返回true
//	if (GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(200.f), Params))
//	{
//		for (TArray<FOverlapResult>::TIterator It(Overlaps); It; ++It) {
//			//如果检测到了玩家
//			if (Cast<ADemoPlayerCharacter>(It->GetActor())) {
//				//赋值
//				SPCharacter = Cast<ADemoPlayerCharacter>(It->GetActor());
//				//如果背包有空间,后面再添加函数
//				if (SPCharacter->IsPackageFree(ObjectIndex))
//				{
//					//停止检测
//					GetWorld()->GetTimerManager().PauseTimer(DetectTimer);
//					//停止销毁定时器
//					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);
//					//关闭物理模拟
//					BoxCollision->SetSimulatePhysics(false);
//				}
//				return;
//			}
//		}
//	}
//}
//
//void ADemoFlobObject::DestroyEvent()
//{
//	if (!GetWorld()) return;
//	//注销定时器
//	GetWorld()->GetTimerManager().ClearTimer(DetectTimer);
//	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
//	//销毁自己
//	GetWorld()->DestroyActor(this);
//}
