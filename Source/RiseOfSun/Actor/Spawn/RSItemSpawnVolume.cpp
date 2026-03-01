#include "Actor/Spawn/RSItemSpawnVolume.h"
#include "Actor/Item/RSBaseItem.h"
 

ARSItemSpawnVolume::ARSItemSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	//Spawing
}

FVector ARSItemSpawnVolume::GetRandomPointInVolume() const
{
	return FVector();
}

void ARSItemSpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!GetWorld()) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	GetWorld()->SpawnActor<ARSBaseItem>(
		GetClass(),
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
}

