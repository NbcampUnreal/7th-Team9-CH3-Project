#include "Actor/Spawn/RSItemSpawnVolume.h"

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

}

