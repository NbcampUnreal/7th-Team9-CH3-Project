// Fill out your copyright notice in the Description page of Project Settings.


#include "RSRifleSceneComponent.h"
#include "RSCharacter.h"
#include "RSPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
URSRifleSceneComponent::URSRifleSceneComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


void URSRifleSceneComponent::BeginPlay()
{
	Super::BeginPlay();



}


void URSRifleSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void URSRifleSceneComponent::Fire(USceneComponent* MuzzlePoint, UNiagaraSystem* MuzzleFlashSystem, FVector AimEnd)
{
	if (AmmoInClip <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Ammo"));
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
	if(!FIreDirection.Normalize())
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
			UE_LOG(LogTemp, Warning, TEXT("attack"));
		}
		// Attack 이후에도 유효한지 다시 체크
		if (IsValid(Target) && Target->IsDead())
		{
			Target->Destroy();
		}
	}

	if (AmmoInClip > 0)
	{



		FRotator Rot = FRotator(0.f, -90.f, 0.f);
		MuzzleFXComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			MuzzleFlashSystem, MuzzlePoint, NAME_None,
			FVector::ZeroVector, Rot,
			EAttachLocation::SnapToTarget, true);

	}
	
	
	AmmoInClip--;
}


void URSRifleSceneComponent::Reload()
{
	if (bIsReloading)
	{
		return;
	}
	if (AmmoInClip == 30)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clip Full"));
		return;
	}
	bIsReloading = true;
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&URSRifleSceneComponent::ReloadComplete,
		ReloadDuration,
		false
	);
}

void URSRifleSceneComponent::ReloadComplete()
{
	AmmoInClip = 30;
	bCanFire = true;
	bIsReloading = false;


}