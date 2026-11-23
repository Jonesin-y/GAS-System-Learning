// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/FireGameplayAbility.h"

#include "Actor/AuraFireProjectile.h"
#include "Interface/CombatInterface.h"

void UFireGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	check(ProjectileClass)
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector Loc = CombatInterface->GetWeaponSocketLoc();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Loc);
		AAuraFireProjectile* SpawnProjectile = GetWorld()->SpawnActorDeferred<AAuraFireProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetAvatarActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		SpawnProjectile->FinishSpawning(SpawnTransform);
		
	}
	
	
}
