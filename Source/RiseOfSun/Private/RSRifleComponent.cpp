

#include "RSRifleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

URSRifleComponent::URSRifleComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	


	
}


void URSRifleComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void URSRifleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void URSRifleComponent::Fire()
{
	if(AmmoInClip <= 0)
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

void URSRifleComponent::Reload()
{
	if(bIsReloading)
	{
		return;
	}
	if(AmmoInClip == 30)
	{
		UE_LOG(LogTemp, Warning, TEXT("Clip Full"));
		return;
	}
	bIsReloading = true;
	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&URSRifleComponent::ReloadComplete,
		ReloadDuration,
		false
	);
}

void URSRifleComponent::ReloadComplete()
{
	AmmoInClip = 30;
	bCanFire = true;
	bIsReloading = false;


}
