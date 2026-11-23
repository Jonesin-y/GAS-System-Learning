// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


void UAttributeMenuWidgetController::BroadCastAllInitialValues()
{
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AuraAS)
	check(AttributeInfo)

	UE_LOG(LogTemp, Warning, TEXT("StrengthTag=%s, MapNum=%d"),
		*Attribute_Primary_Strength.GetTag().ToString(),
		UAuraAttributeSet::GetTagToAttributeMap().Num());

	for (auto& pair : UAuraAttributeSet::GetTagToAttributeMap())
	{
		BroadCastAttributeInfoRow(pair.Key, pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbackToDependenices()
{
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AuraASC)
	check(AuraAS)

	for (auto& pair:UAuraAttributeSet::GetTagToAttributeMap())
	{
		AuraASC->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda(
			[this,pair](const FOnAttributeChangeData&)->void
			{
					BroadCastAttributeInfoRow(pair.Key,pair.Value())	;		
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadCastAttributeInfoRow(const FGameplayTag& GameplayTag,
	const FGameplayAttribute& GameplayAttribute) const
{
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AuraAS)
	FAttributeInfoRow AttributeInfoRow = AttributeInfo->FindAttributeInfoByTag(GameplayTag,true);
	AttributeInfoRow.AttributeValue = GameplayAttribute.GetNumericValue(AuraAS);
	AttributeInfoRowSignature.Broadcast(AttributeInfoRow);
}



