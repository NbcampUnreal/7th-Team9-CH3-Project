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

void ARSMonsterSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (MonsterDataTable) 
	{
		static const FString ContextString(TEXT("MonsterSpawnContext"));
		MonsterDataTable->GetAllRows(ContextString, CachedMonsterRows);
	}
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ARSMonsterSpawnVolume::SpawnNextMonster, 2.0f, true);
}

void ARSMonsterSpawnVolume::SpawnNextMonster()
{
	if (SpawnCount >= MaxSpawnCount)
	{
		// 타이머 멈춤
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}
		// 데이터 테이블이 멀쩡한 지 확인
	if (CachedMonsterRows.IsEmpty()) return;
		// 인덱스 연결이 잘 됐나
	if (CachedMonsterRows.IsValidIndex(CurrentSpawnIndex))
	{	// 현재 인덱스의 데이터 가져오기
		FMonsterSpawnRow* SelectedRow = CachedMonsterRows[CurrentSpawnIndex];
		
		if (SelectedRow && SelectedRow->MonsterClass)
		{	// 실제 스폰 진행
			SpawnMonster(SelectedRow->MonsterClass);
			// 다음 몬스터
			CurrentSpawnIndex++;
			SpawnCount++;
			// 다 소환되면 초기화
			if (CurrentSpawnIndex >= CachedMonsterRows.Num())
			{
				CurrentSpawnIndex = 0;
			}
		}
	}
}

void ARSMonsterSpawnVolume::OnMonsterDestroyed(AActor* DestroyedActor)
{
	ActiveMonsterCount--;

	if (SpawnCount >= MaxSpawnCount && ActiveMonsterCount <= 0)
	{
		LevelUp();
	}
}

void ARSMonsterSpawnVolume::SpawnMonster(TSubclassOf<ARSMonster> MonsterClass)
{
	if (!MonsterClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ARSMonster* NewMonster = GetWorld()->SpawnActor<ARSMonster>(
		MonsterClass,
		GetRandomPointVolume(),
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (NewMonster)
	{
		ActiveMonsterCount++;

		NewMonster->OnDestroyed.AddDynamic(this, &ARSMonsterSpawnVolume::OnMonsterDestroyed);
	}
}

FVector ARSMonsterSpawnVolume::GetRandomPointVolume() const
{	// 박스 크기
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	// 중심 좌표
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxOrigin.Z, BoxOrigin.Z)
	);
}

void ARSMonsterSpawnVolume::LevelUp()
{
	CurrentLevel++;
	MaxSpawnCount += 10;

	SpawnCount = 0;
	CurrentSpawnIndex = 0;

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ARSMonsterSpawnVolume::SpawnNextMonster, 2.0f, true);
}
