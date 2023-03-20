// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DemoSingleton.h"


template<class T>
TSharedPtr<T> DemoSingleton<T>::TInstance = NULL;

template<class T>
TSharedRef<T> DemoSingleton<T>::Create()
{
	TSharedRef<T> TRef = MakeShareable(new T());
	return TRef;
}

template<class T>
void DemoSingleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance = Create();
	}
}

template<class T>
TSharedPtr<T> DemoSingleton<T>::Get()
{
	Initialize();
	return TInstance;
}

