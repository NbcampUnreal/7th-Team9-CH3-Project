// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RSRifleComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RISEOFSUN_API URSRifleComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	URSRifleComponent();
	
public:
	void Fire(USceneComponent* MuzzlePoint, class UNiagaraSystem* MuzzleFlashSystem, FVector AimEnd);
	void Reload();
	
	// 웨폰 트레이스
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TEnumAsByte<ECollisionChannel> WeaponTraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRange = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireDebugDuration = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float ReloadDuration = 0.1f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 AmmoInClip = 30;

protected:
	void ReloadComplete();

	FTimerHandle ReloadTimerHandle;
	bool bIsReloading;

	bool bCanFire = true;

	bool bWantsToFire = false;

	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> MuzzleFXComp;


};
