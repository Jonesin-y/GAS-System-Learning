// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"
class UAbilitySystemComponent;
struct FGameplayEffectContextHandle;

UENUM(BlueprintType)
enum class EffectApplyPolicy : uint8
{
	OnBeginOverlap,
	OnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EffectRemovePolicy : uint8
{
	ReMoveOnEndOverlap,
	DoNotRemove
};

class UGameplayEffect;
class USphereComponent;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraEffectActor();
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffect);
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect>InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	EffectApplyPolicy InstantEffectApplyPolicy = EffectApplyPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect>DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	EffectApplyPolicy DurationEffectApplyPolicy= EffectApplyPolicy::DoNotApply;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect>InfiniteGameplayEffectClass;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	EffectApplyPolicy InfiniteEffectApplyPolicy= EffectApplyPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	EffectRemovePolicy InfiniteEffectRemovePolicy = EffectRemovePolicy::DoNotRemove;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "ApplyEffect")
	float ActorLevel = 1.0f;
private:
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*>ActiveGameplayEffectsHandles;
	
	
		
	
};
