#include "RSMonsterSpawnVolume.h"

#include "Actor/Character/RSMonster.h"
#include "Components/BoxComponent.h"
#include "Data/MonsterSpawnRow.h"

ARSMonsterSpawnVolume::ARSMonsterSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);

	MonsterDataTable = nullptr;
}

void ARSMonsterSpawnVolume::StopSpawning()
{
	bIsSpawning = false;

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawn Stopped"));
}

void ARSMonsterSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (MonsterDataTable) 
	{
		TArray<FMonsterSpawnRow*> RowPtrs;
		static const FString ContextString(TEXT("MonsterSpawnContext"));
		MonsterDataTable->GetAllRows(ContextString, RowPtrs);
		CachedMonsterRows.Reset();
		for (FMonsterSpawnRow* RowPtr : RowPtrs)
		{
			if (RowPtr)
			{
				CachedMonsterRows.Add(*RowPtr); // ✅ 값 복사
			}
		}
    
	}
	
	/*GetWorldTimerManager().SetTimer(SpawnTimerHandle, [this]()
		{
			SpawnNextMonster();
		},2.0f, true);*/
}

void ARSMonsterSpawnVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	GetWorldTimerManager().ClearAllTimersForObject(this);
}



AActor* ARSMonsterSpawnVolume::SpawnNextMonster()
{
	
	if (!bIsSpawning)return nullptr;
	/*if (SpawnCount >= MaxSpawnCount)
	{
		// 타이머 멈춤
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return nullptr;
	}
	*/
		// 데이터 테이블이 멀쩡한 지 확인
	if (CachedMonsterRows.IsEmpty())
	{
		return nullptr;
	}

		// 인덱스 연결이 잘 됐나
		if (CachedMonsterRows.IsValidIndex(CurrentSpawnIndex))
		{	// 현재 인덱스의 데이터 가져오기
			const FMonsterSpawnRow& SelectedRow = CachedMonsterRows[CurrentSpawnIndex];

			if (SelectedRow.MonsterClass)
			{	
				CurrentSpawnIndex++;
				SpawnCount++;
				// 다 소환되면 초기화
				if (CurrentSpawnIndex >= CachedMonsterRows.Num())
				{
					CurrentSpawnIndex = 0;
				}
				
				return SpawnMonster(SelectedRow.MonsterClass);
			}
		}
		return nullptr;
		
	
}

void ARSMonsterSpawnVolume::OnMonsterDestroyed(AActor* DestroyedActor)
{
	ActiveMonsterCount--;

	/*if (SpawnCount == MaxSpawnCount && ActiveMonsterCount == 0)
	{
		LevelUp();
	}*/
}

FMonsterSpawnRow* ARSMonsterSpawnVolume::GetRandomMonster() const
{
	return nullptr;
}

AActor* ARSMonsterSpawnVolume::SpawnMonster(TSubclassOf<ARSMonster> MonsterClass)
{
	if (!MonsterClass) return nullptr;

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
	return NewMonster;
}

FVector ARSMonsterSpawnVolume::GetRandomPointVolume() const
{	// 박스 크기
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	// 중심 좌표
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	float RandomX = FMath::FRandRange(-BoxExtent.X, BoxExtent.X);
	float RandomY = FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y);
	float FixedZ = BoxOrigin.Z - BoxExtent.Z;

	return BoxOrigin + FVector(RandomX, RandomY, -BoxExtent.Z);
}

void ARSMonsterSpawnVolume::LevelUp()
{
	CurrentLevel++;
	MaxSpawnCount += 5;

	SpawnCount = 0;
	CurrentSpawnIndex = 0;

	/*GetWorldTimerManager().SetTimer(SpawnTimerHandle, [this]()
		{
			SpawnNextMonster();
		}, 2.0f, true);*/
}
