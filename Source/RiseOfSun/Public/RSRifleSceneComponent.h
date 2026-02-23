// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RSRifleSceneComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RISEOFSUN_API URSRifleSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URSRifleSceneComponent();
	// 웨폰 트레이스
	TEnumAsByte<ECollisionChannel> WeaponTraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireRange = 10000.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float FireDebugDuration = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float ReloadDuration = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 AmmoInClip = 30;

	struct FTimerHandle ReloadTimerHandle;
	bool bIsReloading;

	bool bCanFire = true;

	bool bWantsToFire = false;

	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> MuzzleFXComp;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire(USceneComponent* MuzzlePoint, class UNiagaraSystem* MuzzleFlashSystem, FVector AimEnd);



	void Reload();

	void ReloadComplete();
};
