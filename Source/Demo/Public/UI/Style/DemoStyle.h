// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEMO_API DemoStyle
{
public:
	static void Initialze();

	static FName GetStyleSetName();			// ��ȡ��ʽ����

	static void ShutDown();					// ��Ϸ�ر�ʱ���ã�ȡ��ע��

	static const ISlateStyle& Get();		// 


private:
	static TSharedRef<class FSlateStyleSet> Create();		// FSlateStyleSet һ��ʯʽ�飬������۵��������Լ��ϡ�
	static TSharedPtr<FSlateStyleSet> DemoStyleInstance;	// 

};
