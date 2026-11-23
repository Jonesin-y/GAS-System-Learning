// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddCharacterAbilities();
	
	virtual void InitAbilityInfo();
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	


};
