#include "Actor/Spawn/RSItemSpawnVolume.h"
#include "Actor/Item/RSBaseItem.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
 

ARSItemSpawnVolume::ARSItemSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	ItemDataTable = nullptr;
}

void ARSItemSpawnVolume::SpawnRandomItem()
{
	if (FRSItemData* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			SpawnItem(ActualClass);
		}
	}
}

FVector ARSItemSpawnVolume::GetRandomPointInVolume() const
{
	const FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

	const FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

FRSItemData* ARSItemSpawnVolume::GetRandomItem() const
{
	if(!ItemDataTable) return nullptr;

	TArray<FRSItemData*>AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())return nullptr;

	float TotalChance = 0.0f;
	for (const FRSItemData* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (FRSItemData* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	return nullptr;
}





void ARSItemSpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	/*if (!GetWorld()) return;

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
	);*/

	/*if (!ItemClass)return;

	GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);*/

	if (!GetWorld() || !ItemClass) return;

	// GetRandomPointInVolume()이 구현되어 있어야 합니다.
	FVector SpawnLocation = GetRandomPointInVolume();
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ItemClass, SpawnLocation, SpawnRotation, SpawnParams);
}

