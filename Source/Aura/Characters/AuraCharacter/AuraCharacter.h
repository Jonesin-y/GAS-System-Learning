// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerState;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitAbilityInfo()override;
	virtual FVector GetWeaponSocketLoc() override;
	UPROPERTY(EditAnywhere,Category = "WeaponSocket")
	FName WeaponSocketTipName;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> weapon;
	UPROPERTY(EditAnywhere,Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(EditAnywhere,Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere,Category = "PlayerState")
	TObjectPtr<AAuraPlayerState> AuraPlayerState;
	
	virtual int32 GetPlayerLevel()override;
};