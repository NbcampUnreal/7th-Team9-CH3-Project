// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RSBaseItem.h"
#include "RSGrenadeItem.generated.h"


UCLASS()
class RISEOFSUN_API ARSGrenadeItem : public ARSBaseItem
{
	GENERATED_BODY()

public:
	ARSGrenadeItem();

protected:
	UPROPERTY(EditAnywhere, Category = "Grenade")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = "Grenade")
	USoundBase* ExplosionSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
	
};
