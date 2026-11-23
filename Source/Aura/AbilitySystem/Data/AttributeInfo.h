// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */
 USTRUCT(BlueprintType)
 struct FAttributeInfoRow
 {
 public:
 	GENERATED_BODY()
 	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "GameplayTag")
 	FGameplayTag GameplayTag;
 	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Name")
 	FText Name;
 	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Description")
 	FText Description;
 	UPROPERTY(BlueprintReadOnly)
 	float AttributeValue;
 	
	 	
 };
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FAttributeInfoRow FindAttributeInfoByTag(FGameplayTag GameplayTag,bool mustFindout);//第二个mustFindout参数表示是否必须找到，如果允许找不到的话就不输出日志，如果必须找到，却还是没找到，就输出错误日志
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AttributeInfoArrayArray")
	TArray<FAttributeInfoRow> AttributeInfoArray;
};
