// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/DemoHandObject.h"
#include "DemoHandHammer.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHandHammer : public ADemoHandObject
{
	GENERATED_BODY()
public:

	ADemoHandHammer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* ExtendMesh;

};
