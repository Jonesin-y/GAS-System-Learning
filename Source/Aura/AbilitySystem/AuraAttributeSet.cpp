// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "AuraGameplayTags.h"
UAuraAttributeSet::UAuraAttributeSet()
{
	// 初始化交给 GE，这里不做任何 Init
}

const TMap<FGameplayTag, AttributeSetFuncPtr>& UAuraAttributeSet::GetTagToAttributeMap()
{
	static const TMap<FGameplayTag, AttributeSetFuncPtr> Map = []()
	{
		TMap<FGameplayTag, AttributeSetFuncPtr> TagToAttribute;
		TagToAttribute.Add(Attribute_Primary_Strength, GetStrengthAttribute);
		TagToAttribute.Add(Attribute_Primary_Intelligence, GetIntelligenceAttribute);
		TagToAttribute.Add(Attribute_Primary_Resilience, GetResilienceAttribute);
		TagToAttribute.Add(Attribute_Primary_Vigor, GetVigorAttribute);
		TagToAttribute.Add(Attribute_Secondary_Armor, GetArmorAttribute);
		TagToAttribute.Add(Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
		TagToAttribute.Add(Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
		TagToAttribute.Add(Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
		TagToAttribute.Add(Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
		TagToAttribute.Add(Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
		TagToAttribute.Add(Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
		TagToAttribute.Add(Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
		TagToAttribute.Add(Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
		TagToAttribute.Add(Attribute_Secondary_MaxMana, GetMaxManaAttribute);
		return TagToAttribute;
	}();
	return Map;
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);

	// Vital Attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);

	// Secondary Attribute
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data,
                                            FEffectProperties& EffectProperties)
{
	//Source表示GameEffect的施加者，Target表示GameEffect的施加对象
	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceASC = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid())
	{
		EffectProperties.SourceActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();//获取PlayerController类
		if (EffectProperties.SourceController == nullptr)//如果PlayerController类为nullptr,那么则判断是否为Pawn,如果是，可能为AIController操控
		{
			if (APawn* pawn = Cast<APawn>(EffectProperties.SourceActor))
			{
				EffectProperties.SourceController = pawn->GetController();
			}
		}
		else//如果SourceController为APlayerController类，则说明对应的AActor为ACharacter类
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceActor);
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid())
	{
		EffectProperties.TargetASC = &Data.Target;
		EffectProperties.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();//获取PlayerController类
		if (EffectProperties.TargetController == nullptr)//如果PlayerController类为nullptr,那么则判断是否为Pawn,如果是，可能为AIController操控
		{
			if (APawn* pawn = Cast<APawn>(EffectProperties.TargetActor))
			{
				EffectProperties.TargetController = pawn->GetController();
			}
		}
		else//如果SourceController为APlayerController类，则说明对应的AActor为ACharacter类
		{
			EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetActor);
		}
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);
}

// ==================== OnRep ====================
// Primary Attribute
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldData);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldData);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldData);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldData);
}

// Vital Attribute
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldData);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldData);
}

// Secondary Attribute
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldData);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldData);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldData);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldData);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldData);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldData);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldData);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldData);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldData);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldData);
}
