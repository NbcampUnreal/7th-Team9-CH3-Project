// Fill out your copyright notice in the Description page of Project Settings.


#include "RSRifleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Actor/Character/RSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
URSRifleComponent::URSRifleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URSRifleComponent::Fire(USceneComponent* MuzzlePoint, UNiagaraSystem* MuzzleFlashSystem, FVector AimEnd)
{
	
	if (bIsReloading)
	{
		return;
	}

	if (AmmoInClip <= 0)
	{
	
		bCanFire = false;
		return;
	}

	bCanFire = true;
	const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(WeaponTraceChannel);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration;

	FVector MuzzleStart = MuzzlePoint->GetComponentLocation();
	FVector FIreDirection = AimEnd - MuzzleStart;
	if (!FIreDirection.Normalize())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Fire Direction"));
		return;
	}

	FVector End = MuzzleStart + (FIreDirection * FireRange);
	FHitResult Hit;

	const bool bIsHit = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		MuzzleStart,
		End,
		TraceType,
		true,
		ActorsToIgnore,
		DrawDebugType,
		Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		FireDebugDuration
	);

	if (bIsHit)
	{
		ARSCharacter* Player = Cast<ARSCharacter>(GetOwner());
		ARSCharacter* Target = Cast<ARSCharacter>(Hit.GetActor());
		
		if (Target && Player)
		{
			Player->Attack(Target); // 실제 데미지 함수 호출
		}
		// Attack 이후에도 유효한지 다시 체크
		if (IsValid(Target) && Target->IsDead())
		{
			Target->Die();
		}
	}
	UGameplayStatics::PlaySoundAtLocation(
			this,
			FireSoundCue,
			MuzzlePoint->GetComponentLocation());
	FRotator Rot = FRotator(0.f, -90.f, 0.f);
	MuzzleFXComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
		MuzzleFlashSystem, MuzzlePoint, NAME_None,
		FVector::ZeroVector, Rot,
		EAttachLocation::SnapToTarget, true);

	AmmoInClip--;

	
	
	OnAmmoChanged.Broadcast(AmmoInClip, MaxAmmoInClip);
}
bool URSRifleComponent::CanFire() const
{
	
	return AmmoInClip > 0;
}

void URSRifleComponent::Reload()
{
	if (bIsReloading)
	{
		return;
	}
	if (AmmoInClip == MaxAmmoInClip)
	{
		return;
	}
	
	OnReloadStarted.Broadcast();
	bIsReloading = true;
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&URSRifleComponent::ReloadComplete,
		ReloadDuration,
		false
	);
	
	UGameplayStatics::PlaySoundAtLocation(
		this,
		ReloadSoundCue,
		GetComponentLocation());
	
}

void URSRifleComponent::ReloadComplete()
{
	AmmoInClip = MaxAmmoInClip;// Fill out your copyright notice in the Description page of Project Settings.
	bCanFire = true; 
	bIsReloading = false;

	OnAmmoChanged.Broadcast(AmmoInClip, MaxAmmoInClip);
}