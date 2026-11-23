// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Characters/AuraCharacter/AuraCharacter.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interface/EnemyInterface.h"
#include "Input/InputDataAsset.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	AuraMappingContext = CreateDefaultSubobject<UInputMappingContext>("InputMapping");
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsLocalController()) return;
	check(InputSubsystem)
	check(AuraMappingContext)
	InputSubsystem->AddMappingContext(AuraMappingContext,0);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	
	
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	AuraInputComponent->BindAbilitiesInput(InputConfig,this,&ThisClass::PressedFunc,&ThisClass::HeldFunc,&ThisClass::ReleasedFunc);
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
	AutoRun();
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,CursorHit);
	LastActor = CurActor;
	CurActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	if (LastActor!=CurActor)
	{
		if (LastActor)LastActor->UnHightLight();
		if (CurActor)CurActor->HightLight();
	}
	
}


void AAuraPlayerController::Move(const FInputActionValue& InputValue)
{
	FVector2D InputAxis = InputValue.Get<FVector2D>();
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
	FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	APawn* player = GetPawn<APawn>();
	if (player == nullptr) return;
	player->AddMovementInput(ForwardDir,InputAxis.Y);
	player->AddMovementInput(RightDir,InputAxis.X);
	
	
}

void AAuraPlayerController::PressedFunc(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())return;
	if (InputTag.MatchesTag(Input_RMB_1))
	{
		bAutoRun = false;
		FollowTime = 0.0f;
		bTouchingSomething = CurActor ? true : false;
		CashedLocation = FVector::Zero();
	}
	
}

void AAuraPlayerController::ReleasedFunc(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())return;
	UAuraAbilitySystemComponent* ASC = GetAuraASC();
	if (ASC)
	{
		if (InputTag.MatchesTag(Input_RMB_1))
		{
			if (bTouchingSomething)
			{
				ASC->AbilityInputTagReleased(InputTag);
				return;
			}
			else if (FollowTime <= MaxHeldTime)
			{
				UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
				FNavLocation Destination;
				NavSystem->ProjectPointToNavigation(CashedLocation,Destination,FVector(300.0f,300.0f,300.0f));//寻找在CashedLocation附近，距离其最近，有Nav网格的一个目标位置，并存到Destination中
				if (UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,GetPawn()->GetActorLocation(),Destination.Location))
				{
					Spline->ClearSplinePoints();
					for (const FVector& PointLoc : NavigationPath->PathPoints)
					{
						Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
						//DrawDebugSphere(GetWorld(),PointLoc,8.f,8,FColor::Green,false,5.0f,1);
					}
					bAutoRun = true;
				}
			}
		}
		FollowTime = 0.f;
		ASC->AbilityInputTagReleased(InputTag);
		
	}
}

void AAuraPlayerController::HeldFunc(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())return;
	UAuraAbilitySystemComponent* ASC = GetAuraASC();
	if (ASC)
	{
		if (InputTag.MatchesTag(Input_RMB_1))
		{
			FollowTime+=GetWorld()->GetDeltaSeconds();
			bTouchingSomething = CurActor ? true : false;
			if (bTouchingSomething)
			{
				ASC->AbilityInputTagHeld(InputTag);
				CashedLocation = CursorHit.Location;
				return;
			}
			else
			{
				CashedLocation = CursorHit.Location;
				FVector Direction = CashedLocation - GetPawn()->GetActorLocation();
				GetPawn()->AddMovementInput(Direction);
				
			}
		}
		ASC->AbilityInputTagHeld(InputTag);
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraASC()
{
	if (AuraASC == nullptr)
	{
		if (AAuraCharacter* AuraPlayer = Cast<AAuraCharacter>(GetPawn()))
		{
			AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPlayer->AbilitySystemComponent);
			return AuraASC;
		}
	}
	return AuraASC;
}

void AAuraPlayerController::AutoRun()
{
	if (bAutoRun)
	{
		if (APawn* ControllerPawn = GetPawn())
		{
			FVector LocOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
			FVector Dir = Spline->FindDirectionClosestToWorldLocation(LocOnSpline,ESplineCoordinateSpace::World);//获取最后的有效位置用于计算是否停止，而不是用CashedLocation计算
			FVector Destination = FVector::Zero();
			int LastIndex = Spline->GetNumberOfSplinePoints()-1;
			if (LastIndex>0)
			{
				 Destination = Spline->GetLocationAtSplinePoint(LastIndex,ESplineCoordinateSpace::World);
			}
			float SourceToTarDistance = (LocOnSpline-Destination).Length();
			ControllerPawn->AddMovementInput(Dir);
			if (SourceToTarDistance <= ReachedRadius)
			{
				bAutoRun = false;
			}			
		}
	}
}
