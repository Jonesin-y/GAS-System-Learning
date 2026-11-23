// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastAllInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	
}

void UOverlayWidgetController::BindCallbackToDependenices()
{
	Super::BindCallbackToDependenices();
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData&	Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
	{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
			OnMaxManaChanged.Broadcast(Data.NewValue);
	}
	);
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		AuraASC->AssetTagsSignature.AddLambda(
			[this](FGameplayTagContainer AssetTags)
			{
				for (auto& Tag : AssetTags)
				{
					FUIWidgetRow* row = GetUIWidgetRowByTag<FUIWidgetRow>(UIDataTable,Tag);
					if (row==nullptr)
					{
						GEngine->AddOnScreenDebugMessage(-1,4,FColor::Blue,FString::Printf(TEXT("Row not Exist!")));
						return;
					}
					OnUIWidgetRowReceived.Broadcast(*row);
				}
			}
		);
	}
	
}




