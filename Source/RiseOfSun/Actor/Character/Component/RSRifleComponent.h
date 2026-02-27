// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RSRifleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, AmmoInClip, int32, MaxAmmoInClip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadStarted);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RISEOFSUN_API URSRifleComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	URSRifleComponent();

	UPROPERTY(BlueprintAssignable)
	FOnReloadStarted OnReloadStarted;
public:
	void Fire(USceneComponent* MuzzlePoint, class UNiagaraSystem* MuzzleFlashSystem, FVector AimEnd);
	bool CanFire() const;
	void Reload();
	
	// 웨폰 트레이스
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TEnumAsByte<ECollisionChannel> WeaponTraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRange = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireDebugDuration = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float ReloadDuration = 2.0f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 AmmoInClip = 30;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 MaxAmmoInClip = 30;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundCue> ReloadSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundCue> FireSoundCue;
protected:
	void ReloadComplete();

	FTimerHandle ReloadTimerHandle;
	bool bIsReloading;

	bool bCanFire = true;

	bool bWantsToFire = false;

	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> MuzzleFXComp;


};
