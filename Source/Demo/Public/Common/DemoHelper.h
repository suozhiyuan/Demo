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
	 *	一个延时调用的委托，在声音播放完毕后调用方法
	 *	定时器相关知识
	 *	定义定时器句柄		FTimerHandle mTimer
	 *	定义调用的委托		FTimerDelegate timeDele;
	 *	绑定函数到委托		timeDele.BindRaw(要委托类的类型指针, 要委托的函数指针);
	 *	获取时间控制器并且启动定时器
	 *
	 *	Gworld->GetTimerManager().SetTimer(mlime, timeDele, 1.f, true);
	 *	Gworld->GetTimerManager().PauseTimer(mTimer);                    //暂停
	 *	Gworld->GetTimerManager().UnPauseTimer(mTimer);					 //唤醒
	 *	Gworld->GetTimerManager().ClearTimer(mlimer);                    //清除计时器
	 *
	 */
	template<class UserClass>
	FORCEINLINE FTimerHandle PlayerSoundAndCall(UWorld* World, const FSlateSound Sound, UserClass* InUserObject, typename FTimerDelegate::TRawMethodDelegate<UserClass>::FMethodPtr InMethod)
	{
		// 先播放音乐
		FSlateApplication::Get().PlaySound(Sound);

		// 时间控制的句柄
		FTimerHandle Result;

		// 获取音乐播放的时间，最短0.1
		const float SoundDuration = FMath::Max(FSlateApplication::Get().GetSoundDuration(Sound), 0.1f);

		// 时间委托
		FTimerDelegate Callback;

		// 绑定传入的 委托类的指针，以及函数的指针
		Callback.BindRaw(InUserObject, InMethod);

		World->GetTimerManager().SetTimer(Result, Callback, SoundDuration, false);
		return Result;
	}
}
