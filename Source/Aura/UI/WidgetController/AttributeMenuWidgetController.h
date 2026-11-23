// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"
struct FGameplayAttribute;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoRowSignature, const FAttributeInfoRow&, NewAttributeInfoRow);
/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoRowSignature AttributeInfoRowSignature;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AttributeInfo")
	TObjectPtr<UAttributeInfo> AttributeInfo;
	virtual void BroadCastAllInitialValues() override;
	virtual void BindCallbackToDependenices()override;
protected:
	
private:
	void BroadCastAttributeInfoRow(const FGameplayTag& GameplayTag,const FGameplayAttribute& GameplayAttribute)const;
};
