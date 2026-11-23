// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UInputDataAsset;
class UInputAction;
/**
 * 
 */
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class USplineComponent;
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void BeginPlay() override;
	
protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	
	void CursorTrace();
	FHitResult CursorHit;
	IEnemyInterface* LastActor = nullptr;
	IEnemyInterface* CurActor= nullptr;
	
	void Move(const FInputActionValue& InputValue);
	void PressedFunc(FGameplayTag InputTag);
	void ReleasedFunc(FGameplayTag InputTag);
	void HeldFunc(FGameplayTag InputTag);
	UAuraAbilitySystemComponent* GetAuraASC();
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Input|InputConfig")
	TObjectPtr<UInputDataAsset> InputConfig;
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	TObjectPtr<UAuraAbilitySystemComponent> AuraASC;
	
	//Clicked Move
	FVector CashedLocation = FVector();
	float FollowTime = 0.0f;
	float MaxHeldTime = 0.5f;//如果按下的时间超过这个值，则使用自动寻路
	float ReachedRadius = 50.0f;//如果距离目标点距离小于等于该距离，则停止移动
	bool bTouchingSomething = false;
	bool bAutoRun = false;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	void AutoRun();
	
	
};
