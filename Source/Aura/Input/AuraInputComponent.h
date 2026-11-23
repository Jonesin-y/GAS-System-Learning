// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputDataAsset.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass,typename PressedFunc,typename HeldFunc,typename ReleasedFunc>
	void BindAbilitiesInput(UInputDataAsset* InputConfig,UserClass* Object,PressedFunc PressedFuncPtr,HeldFunc HeldFuncPtr,ReleasedFunc ReleasedFuncPtr);
};

template <class UserClass, typename PressedFunc, typename HeldFunc, typename ReleasedFunc>
void UAuraInputComponent::BindAbilitiesInput(UInputDataAsset* InputConfig, UserClass* Object, PressedFunc PressedFuncPtr,
	HeldFunc HeldFuncPtr, ReleasedFunc ReleasedFuncPtr)
{
	for (FAuraInputAction& AuraInputAction : InputConfig->InputConfig)
	{
		if (PressedFuncPtr!=nullptr)
		{
			BindAction(AuraInputAction.InputAction,ETriggerEvent::Started,Object,PressedFuncPtr,AuraInputAction.InputTag);
		}
		if (HeldFuncPtr!=nullptr)
		{
			BindAction(AuraInputAction.InputAction,ETriggerEvent::Triggered,Object,HeldFuncPtr,AuraInputAction.InputTag);
		}
		if (ReleasedFuncPtr)
		{
			BindAction(AuraInputAction.InputAction,ETriggerEvent::Completed,Object,ReleasedFuncPtr,AuraInputAction.InputTag);
		}
	}
}
