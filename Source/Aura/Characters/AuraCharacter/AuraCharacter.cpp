// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
class AAuraHUD;

AAuraCharacter::AAuraCharacter()
{
	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,400.0f,0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetRelativeRotation(FRotator(-50.0f,0.0f,0.0f));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	
	
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init Ability Actor For the Server
	InitAbilityInfo();
	AddCharacterAbilities();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init Ability Actor For the Client
	InitAbilityInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::InitAbilityInfo()
{
	AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState)
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		AuraASC->AbilityInfoSet();
		//InitAbilityActorInfo之后，再用GE初始化Attribute
		AuraASC->InitAttributeValue();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,4,FColor::Blue,FString::Printf(TEXT("AuraASC doesn't exist")));
	}
	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PC -> IsLocalController())
		{
			if (PC->GetHUD()!=nullptr)
			{
				AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD());
				HUD->InitOverLay(PC,AuraPlayerState,AbilitySystemComponent,AttributeSet);
			}
		}
	}
}

FVector AAuraCharacter::GetWeaponSocketLoc()
{
	check(weapon)
	return weapon->GetSocketLocation(WeaponSocketTipName);
}

int32 AAuraCharacter::GetPlayerLevel()
{
	return AuraPlayerState->GetPlayerLevel();
}

