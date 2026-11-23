// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AurAbilitySystemLibrary.h"

#include "AuraAbilitySystemComponent.h"
#include "Characters/AuraCharacter/AuraCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAurAbilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	AAuraPlayerController* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	if (PC!=nullptr)
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PlayerState = Cast<AAuraCharacter>(PC->GetCharacter())->AuraPlayerState;
			UAbilitySystemComponent* ASC = PlayerState->AbilitySystemComponent;
			UAttributeSet* AttributeSet = PlayerState->AttributeSet;
			FWidgetControllerParams Params(PC,PlayerState,ASC,AttributeSet);
			UOverlayWidgetController* OverlayWidgetController = Cast<UOverlayWidgetController>(HUD->GetOverlayWidgetController(Params));
			
			return OverlayWidgetController;
			
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAurAbilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContextObject)
{
	AAuraPlayerController* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	if (PC!=nullptr)
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PlayerState = Cast<AAuraCharacter>(PC->GetCharacter())->AuraPlayerState;
			UAbilitySystemComponent* ASC = PlayerState->AbilitySystemComponent;
			UAttributeSet* AttributeSet = PlayerState->AttributeSet;
			FWidgetControllerParams Params(PC,PlayerState,ASC,AttributeSet);
			UAttributeMenuWidgetController* AttributeMenuWidgetController = Cast<UAttributeMenuWidgetController>(HUD->GetAttributeMenuWidgetController(Params));
			//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("GetAttributeMenuWidgetController!"));
			return AttributeMenuWidgetController;
		}
	}
	return nullptr;
}
