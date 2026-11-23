// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,FGameplayTagContainer)
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityInfoSet();
	void InitAttributeValue();
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	FEffectAssetTags AssetTagsSignature;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "InitialAttributeEffect")
	TSubclassOf<UGameplayEffect> PrimaryAttributeInitGE;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "InitialAttributeEffect")
	TSubclassOf<UGameplayEffect> SecondaryAttributeInitGE;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "InitialAttributeEffect")
	TSubclassOf<UGameplayEffect> VitalAttributeInitGE;
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
protected:
	UFUNCTION(Client,Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
};
