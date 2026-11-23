// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"

const UAuraAssetManager& UAuraAssetManager::Get()
{
	UAuraAssetManager* MyAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	// GameplayTag 现在通过 UE_DEFINE_GAMEPLAY_TAG 在模块加载时静态注册，这里不再需要手动初始化
	Super::StartInitialLoading();
}
