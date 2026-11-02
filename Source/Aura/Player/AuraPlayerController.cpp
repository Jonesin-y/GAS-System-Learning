// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	AuraMappingContext = CreateDefaultSubobject<UInputMappingContext>("InputMapping");
	
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
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
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,CursorHit);
	LastActor = CurActor;
	CurActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	/*
	 * 五种情况
	 * 1:LastActor == nullptr,CurActor == nullptr
	 *  Nothing to Do
	 * 2:LastActor == nullptr,CurActor !=nullptr
	 *  Highlighting
	 * 3:LastActor != nullptr,CurActor == nullptr
	 *  UnHighlighting
	 * 4:LastActor !=nullptr,CurActor != nullptr,CurActor != LastActor
	 *  UnHightlighting LastActor,Highlighting CurActor
	 * 5:LastActor != nullptr,CurActor != nullptr,CurActor == LastActor
	 *  Nothing to Do
	 */
	if (LastActor == nullptr)
	{
		if (CurActor != nullptr)
		{
			CurActor->HightLight();
		}
		else if (CurActor == nullptr)
		{
		}
	}
	else if (LastActor != nullptr)
	{
		if (CurActor != nullptr && LastActor != CurActor)
		{
			LastActor->UnHightLight();
			CurActor->HightLight();
		}
		else if (CurActor != nullptr && LastActor == CurActor)
		{
		}
		else if (CurActor == nullptr)
		{
			LastActor->UnHightLight();
		}
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
	check(player)
	player->AddMovementInput(ForwardDir,InputAxis.Y);
	player->AddMovementInput(RightDir,InputAxis.X);
	
	
}
