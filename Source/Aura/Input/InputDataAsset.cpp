// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputDataAsset.h"

UInputAction* UInputDataAsset::FindInputActionByTag(FGameplayTag GameplayTag)
{
	for (FAuraInputAction& InputAction:InputConfig)
	{
		if (InputAction.InputTag.MatchesTag(GameplayTag))
			return InputAction.InputAction;
	}
	return nullptr;
}
