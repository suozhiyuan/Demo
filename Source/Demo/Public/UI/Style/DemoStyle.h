// �����������ǣ���ȡ�����ʽ���Լ��ѷ��ע�����Ϸ

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
class DEMO_API DemoStyle
{
public:
	static void Initialze();

	static FName GetStyleSetName();			// ��ȡ��ʽ���֣����������ע�����Ϸ�е�����

	static void ShutDown();					// ��Ϸ�ر�ʱ���ã�ȡ��ע��

	static const ISlateStyle& Get();		// ���ⲿ���ã���ȡ�������

private:

	static TSharedRef<class FSlateStyleSet> Create();		//FSlateStyleSet��ģ�壬һ��������۵����Լ���,����ע����ʽ
	static TSharedPtr<FSlateStyleSet> DemoStyleInstance;	//��Ϊ����ģʽ���������һ�����ܷŵ����캯����ȥʵ��

};
