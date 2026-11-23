// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraAttributeSet.h"
#include "AuraGameplayTags.h"
#include "Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);
	const FString ArmorTagString = Attribute_Secondary_Armor.GetTag().ToString();
	GEngine->AddOnScreenDebugMessage(-1,4,FColor::Orange,ArmorTagString);
}

void UAuraAbilitySystemComponent::InitAttributeValue()
{
	check(PrimaryAttributeInitGE)
	check(SecondaryAttributeInitGE)
	check(GetSet<UAuraAttributeSet>());
	//Init Primary Attribute
	FGameplayEffectContextHandle GEContextHandle = this->MakeEffectContext();
	check(this->GetAvatarActor())
	GEContextHandle.AddSourceObject(this->GetAvatarActor());
	FGameplayEffectSpecHandle PrimaryGESpecHandle= this->MakeOutgoingSpec(PrimaryAttributeInitGE,1.f,GEContextHandle);
	this->ApplyGameplayEffectSpecToSelf(*PrimaryGESpecHandle.Data.Get());
	//Init Secondary Attribute
	FGameplayEffectSpecHandle SecondaryGESpecHandle = this->MakeOutgoingSpec(SecondaryAttributeInitGE,1.f,GEContextHandle);
	this->ApplyGameplayEffectSpecToSelf(*SecondaryGESpecHandle.Data.Get());
	//Init Vital Attribute
	FGameplayEffectSpecHandle VitalGESpecHandle = this->MakeOutgoingSpec(VitalAttributeInitGE,1.f,GEContextHandle);
	this->ApplyGameplayEffectSpecToSelf(*VitalGESpecHandle.Data.Get());
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (TSubclassOf<UGameplayAbility>& AbilityClass:Abilities)
	{
		
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		if (UAuraGameplayAbility* Ability = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability->InputTag);
		}
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
			
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer AssetTagsContainer;
	GameplayEffectSpec.GetAllAssetTags(AssetTagsContainer);
	AssetTagsSignature.Broadcast(AssetTagsContainer);
}


