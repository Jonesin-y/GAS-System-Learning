// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include <numbers>

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

class IAbilitySystemInterface;
// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
	
}



void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC==nullptr)return;
	FGameplayEffectContextHandle GEContext = TargetASC->MakeEffectContext();
	GEContext.AddSourceObject(this);
	FGameplayEffectSpecHandle GESpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffect,ActorLevel,GEContext);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data.Get());
	bool IsInfiniteEffect = GESpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (IsInfiniteEffect && InfiniteEffectRemovePolicy == EffectRemovePolicy::ReMoveOnEndOverlap)
	{
		ActiveGameplayEffectsHandles.Add(ActiveEffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EffectApplyPolicy::OnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplyPolicy == EffectApplyPolicy::OnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplyPolicy == EffectApplyPolicy::OnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EffectApplyPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplyPolicy == EffectApplyPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplyPolicy == EffectApplyPolicy::OnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovePolicy == EffectRemovePolicy::ReMoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		TArray<FActiveGameplayEffectHandle>ToRemoveActiveEffectHandles;
		for (TTuple<FActiveGameplayEffectHandle,UAbilitySystemComponent*>& pair: ActiveGameplayEffectsHandles)
		{
			TargetASC->RemoveActiveGameplayEffect(pair.Key,1);
			ToRemoveActiveEffectHandles.Add(pair.Key);
		}
		for (auto& handle: ToRemoveActiveEffectHandles)
		{
			ActiveGameplayEffectsHandles.FindAndRemoveChecked(handle);
		}
	}
}

