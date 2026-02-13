#include "RSMonsterSpawnVolume.h"
#include "Components/BoxComponent.h"

ARSMonsterSpawnVolume::ARSMonsterSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	MonsterDataTable = nullptr;
}

void ARSMonsterSpawnVolume::SpawnRandomMonster()
{
	if (FMonsterSpawnRow* SelectedRow = GetRandomMonster())
	{
		if (UClass* ActualClass = SelectedRow->MonsterClass.Get())
		{
			SpawnMonster(ActualClass);
		}
	}
}

FMonsterSpawnRow* ARSMonsterSpawnVolume::GetRandomMonster() const
{
	if (!MonsterDataTable) return nullptr;

	TArray<FMonsterSpawnRow*> AllRows;
	static const FString ContextString(TEXT("MonsterSpawnContext"));
	MonsterDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FMonsterSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	
	float AccumulateChance = 0.0f;

	for (FMonsterSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

void ARSMonsterSpawnVolume::SpawnMonster(TSubclassOf<ARSMonster> MonsterClass)
{
	if (!MonsterClass) return;

	GetWorld()->SpawnActor<ARSMonster>(
		MonsterClass,
		GetRandomPointVolume(),
		FRotator::ZeroRotator
	);
}

FVector ARSMonsterSpawnVolume::GetRandomPointVolume() const
{	// 박스 크기
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	// 중심 좌표
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}