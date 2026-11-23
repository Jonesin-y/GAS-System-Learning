// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

FWidgetControllerParams::FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
		:PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS)
{
}



void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& FWCP)
{
	PlayerController = FWCP.PlayerController;
	PlayerState = FWCP.PlayerState;
	AbilitySystemComponent = FWCP.AbilitySystemComponent;
	AttributeSet = FWCP.AttributeSet;
}

void UAuraWidgetController::BroadCastAllInitialValues()
{
}

void UAuraWidgetController::BindCallbackToDependenices()
{
}

