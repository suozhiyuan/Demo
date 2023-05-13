// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace DemoHelper
{

	FORCEINLINE void Debug(FString Message, float Duration = 3.f)
	{
		if (GEngine) 
		{
			GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Yellow, Message);
		}
	}

	/**
	 *	һ����ʱ���õ�ί�У�������������Ϻ���÷���
	 *	��ʱ�����֪ʶ
	 *	���嶨ʱ�����		FTimerHandle mTimer
	 *	������õ�ί��		FTimerDelegate timeDele;
	 *	�󶨺�����ί��		timeDele.BindRaw(Ҫί���������ָ��, Ҫί�еĺ���ָ��);
	 *	��ȡʱ�����������������ʱ��
	 *
	 *	Gworld->GetTimerManager().SetTimer(mlime, timeDele, 1.f, true);
	 *	Gworld->GetTimerManager().PauseTimer(mTimer);                    //��ͣ
	 *	Gworld->GetTimerManager().UnPauseTimer(mTimer);					 //����
	 *	Gworld->GetTimerManager().ClearTimer(mlimer);                    //�����ʱ��
	 *
	 */
	template<class UserClass>
	FORCEINLINE FTimerHandle PlayerSoundAndCall(UWorld* World, const FSlateSound Sound, UserClass* InUserObject, typename FTimerDelegate::TRawMethodDelegate<UserClass>::FMethodPtr InMethod)
	{
		// �Ȳ�������
		FSlateApplication::Get().PlaySound(Sound);

		// ʱ����Ƶľ��
		FTimerHandle Result;

		// ��ȡ���ֲ��ŵ�ʱ�䣬���0.1
		const float SoundDuration = FMath::Max(FSlateApplication::Get().GetSoundDuration(Sound), 0.1f);

		// ʱ��ί��
		FTimerDelegate Callback;

		// �󶨴���� ί�����ָ�룬�Լ�������ָ��
		Callback.BindRaw(InUserObject, InMethod);

		World->GetTimerManager().SetTimer(Result, Callback, SoundDuration, false);
		return Result;
	}
}
