// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AAuraHUD::InitOverLay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("AuraUserWidgetClass doesn't exist , pls fill in AuraHUD class"))
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(),OverlayWidgetClass);
	checkf(OverlayWidgetControllerClass,TEXT("AuraWidgetController doesn't exist,pls fill in AuraHUD class"))\
	FWidgetControllerParams params = FWidgetControllerParams(PC,PS,ASC,AS);
	OverlayWidgetController = Cast<UOverlayWidgetController>(GetOverlayWidgetController(params));
	
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadCastAllInitialValues();
	OverlayWidget->AddToViewport();
}

UAuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbackToDependenices();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UAuraWidgetController* AAuraHUD::GetAttributeMenuWidgetController(
	const FWidgetControllerParams& AttributeMenuControllerParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this,AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(AttributeMenuControllerParams);
		AttributeMenuWidgetController->BindCallbackToDependenices();
		return AttributeMenuWidgetController;
	}
	return AttributeMenuWidgetController;
}
