// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyCharacter.h"
#include "GobolinCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AGobolinCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AGobolinCharacter();
	virtual void HightLight() override;
	virtual void UnHightLight() override;
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> weapon;
};
