// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AuraHUD.generated.h"

class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UAuraWidgetController;
class UAuraUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	void InitOverLay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);

	UAuraWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	UAuraWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& AttributeMenuControllerParams);
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraUserWidget>OverlayWidget;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeMenuWidgetController>AttributeMenuWidgetController;
	

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> AttributeMenuWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	
};
