// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTool/DemoEnemyWeapon.h"

#include "Components/BoxComponent.h"
#include "Player/DemoPlayerCharacter.h"


ADemoEnemyWeapon::ADemoEnemyWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_GreatAxe_01.SM_Wep_GreatAxe_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-38.f, 9.6f, 9.8f));
	BaseMesh->SetRelativeRotation(FRotator(-10.f, 76.5f, -99.f));
	BaseMesh->SetRelativeScale3D(FVector(0.75f));

	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 158.f));
	AffectCollision->SetRelativeScale3D(FVector(1.125f, 0.22f, 1.f));
}

void ADemoEnemyWeapon::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADemoPlayerCharacter>(OtherActor))		// 交互物品是不是玩家，如果是玩家则减血
	{
		Cast<ADemoPlayerCharacter>(OtherActor)->AcceptDamage(20);
	}
}