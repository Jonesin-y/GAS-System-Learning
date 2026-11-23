// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
AEnemyCharacter::AEnemyCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		AuraASC->AbilityInfoSet();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,4,FColor::Blue,FString::Printf(TEXT("AuraASC doesn't exist")));
	}
}



void AEnemyCharacter::HightLight()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AEnemyCharacter::UnHightLight()
{
	GetMesh()->SetRenderCustomDepth(false);
}

