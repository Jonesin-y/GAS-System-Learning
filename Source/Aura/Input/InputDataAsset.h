// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
UCLASS()
class AURA_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UInputAction* FindInputActionByTag(FGameplayTag GameplayTag);
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraInputAction> InputConfig;
	
};
