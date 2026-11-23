// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "AuraAttributeSet.generated.h"

typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr AttributeSetFuncPtr;

/**
 * 
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
public:
	FEffectProperties() = default;
	UPROPERTY()
	AActor* SourceActor = nullptr;
	UPROPERTY()
	AActor* TargetActor = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	FGameplayEffectContextHandle EffectContextHandle;
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	static const TMap<FGameplayTag,AttributeSetFuncPtr>& GetTagToAttributeMap();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	AttributeSetFuncPtr FunctionPointer;
	// ==================== Primary Attribute ====================
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Vigor)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Resilience)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	// ==================== Vital Attribute ====================
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	// ==================== Secondary Attribute ====================
	// 由 Vigor 决定
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	// 由 Intelligence 决定
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	// 由 Resilience 决定：减少受到的伤害，并提高格挡几率
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor)

	// 由 Resilience 决定：无视敌人部分护甲，并提高暴击几率
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration)

	// 由 Armor 决定：格挡时伤害减半的几率
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance)

	// 由 ArmorPenetration 决定：造成双倍伤害（加暴击加成）的几率
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance)

	// 由 ArmorPenetration 决定：暴击时额外增加的伤害
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage)

	// 由 Armor 决定：降低敌人对自己的暴击几率
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance)

	// 由 Vigor 决定：每秒恢复的生命值
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration)

	// 由 Intelligence 决定：每秒恢复的法力值
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration)

	// ==================== OnRep ====================
	// Primary Attribute
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldData);

	// Vital Attribute
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldData);

	// Secondary Attribute
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldData);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldData);

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
};
