// Fill out your copyright notice in the Description page of Project Settings.


#include "RSRifleSceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
URSRifleSceneComponent::URSRifleSceneComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	RifleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RifleMesh2"));
	/*RifleMesh->SetupAttachment(this);*/

	MuzzlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePoint2"));
	/*MuzzlePoint->SetupAttachment(RifleMesh);*/
	



}


void URSRifleSceneComponent::BeginPlay()
{
	Super::BeginPlay();



}


void URSRifleSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void URSRifleSceneComponent::Fire()
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

	FVector Start = GetComponentLocation();

	FVector End = GetComponentLocation() + GetForwardVector() * FireRange;

	FHitResult Hit;

	const bool bIsHit = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
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