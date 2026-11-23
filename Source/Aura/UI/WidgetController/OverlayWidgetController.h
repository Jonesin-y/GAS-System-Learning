// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"


#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag Tag = FGameplayTag();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UUserWidget> MessageWidget;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIWidgetRowSignature,FUIWidgetRow,NewUIWidgetRow);


/**
 * 
 */

UCLASS(Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadCastAllInitialValues() override;
	virtual void BindCallbackToDependenices() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Data|UIDataTable")
	TObjectPtr<UDataTable> UIDataTable;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attribute")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable,Category = "DataTable|UIDataTable")
	FOnUIWidgetRowSignature OnUIWidgetRowReceived;
protected:
	template<typename T>
	T* GetUIWidgetRowByTag(UDataTable* dataTable,const FGameplayTag& GameplayTag)
	{
		if (dataTable == nullptr) return nullptr;
		return dataTable->FindRow<T>(GameplayTag.GetTagName(),TEXT("Doesn,t Exist!"));
	}
	
	
};
