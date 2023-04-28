// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/DemoSceneCapture2D.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"


ADemoSceneCapture2D::ADemoSceneCapture2D()
{
	//����ÿ֡����
	GetCaptureComponent2D()->bCaptureEveryFrame = true;

	//������ȾͼƬ�ĸ�ʽ����Ȼ��Ⱦ������ͼƬ����������
	GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	//������ҰģʽΪ����ģʽ
	GetCaptureComponent2D()->ProjectionType = ECameraProjectionMode::Orthographic;

	//���ó�ʼ������Ұ��ΧΪ3000
	GetCaptureComponent2D()->OrthoWidth = 3000.f;

	//������ת,ͷ����,�Ժ�ֻ�ı����������
	SetActorRotation(FRotator(-90.f, 0.f, 0.f));
}

UTextureRenderTarget2D* ADemoSceneCapture2D::GetMiniMapTex()
{
	//������Ⱦ��ͼ
	MiniMapTex = NewObject<UTextureRenderTarget2D>();

	//�����4�ı���
	MiniMapTex->InitAutoFormat(256, 256);

	//�󶨵���Ⱦ�����
	GetCaptureComponent2D()->TextureTarget = MiniMapTex;

	//������Դ
	return MiniMapTex;
}

void ADemoSceneCapture2D::UpdateTransform(FVector NormLocation, FRotator NormRotator)
{
	//����λ��Ϊ����Ϸ�1000
	SetActorLocation(NormLocation + FVector(0.f, 0.f, 1000.f));

	//������תΪ�����ת
	SetActorRotation(FRotator(-90.f, NormRotator.Yaw, NormRotator.Roll));
}

void ADemoSceneCapture2D::UpdateMiniMapWidth(int Delta)
{
	const float PreWidth = GetCaptureComponent2D()->OrthoWidth;
	GetCaptureComponent2D()->OrthoWidth = FMath::Clamp<float>(PreWidth + Delta, 2000.f, 4000.f);		// �޸Ŀ��
}

float ADemoSceneCapture2D::GetMapSize()
{
	return GetCaptureComponent2D()->OrthoWidth;
}