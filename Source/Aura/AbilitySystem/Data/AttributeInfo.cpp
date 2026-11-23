// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAttributeInfoRow UAttributeInfo::FindAttributeInfoByTag(FGameplayTag GameplayTag,bool mustFindout)
{
	for (FAttributeInfoRow& Info : AttributeInfoArray)
	{
		if (Info.GameplayTag.MatchesTag(GameplayTag))
		{
			return Info;
		}
	}
	if (mustFindout)
	{
		UE_LOG(LogTemp,Warning,TEXT("AttributeInfo Can't Find The GameplayTag"));
	}
	return FAttributeInfoRow();
}
