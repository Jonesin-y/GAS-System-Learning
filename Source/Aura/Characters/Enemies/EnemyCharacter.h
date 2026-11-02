// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	UAttributeSet* GetAttributeSet() const {return AttributeSet;};
	//Start EnemyInterface
	virtual void HightLight() override;
	virtual void UnHightLight() override;
	//End EnemyInterface
protected:
	AEnemyCharacter();
	virtual void BeginPlay() override;
	
	
	
};
