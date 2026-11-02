 // Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/GobolinCharacter.h"

AGobolinCharacter::AGobolinCharacter()
{
	weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

 void AGobolinCharacter::HightLight()
 {
	 Super::HightLight();
	weapon->SetRenderCustomDepth(true);
	weapon->SetCustomDepthStencilValue(250);
 }

 void AGobolinCharacter::UnHightLight()
 {
	 Super::UnHightLight();
	weapon->SetRenderCustomDepth(false);
 }
