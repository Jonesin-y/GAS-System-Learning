// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraFireProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class AURA_API AAuraFireProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraFireProjectile();

	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
