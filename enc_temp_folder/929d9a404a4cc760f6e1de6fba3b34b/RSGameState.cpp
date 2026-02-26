

#include "RSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Spawn/RSMonsterSpawnVolume.h"
#include "Actor/Character/RSMonster.h"
#include "EngineUtils.h"

ARSGameState::ARSGameState()
{
	Score = 0;
	MonsterCount = 0;
	KillMonsterCount = 0;
	CurrentLevelIndex = 0;
	RewardSpawnLocation = FVector(0.f, 0.f, 100.f);
}

void ARSGameState::BeginPlay()
{
	Super::BeginPlay();
	FindMainLight(); // 시작하자마자 조명을 찾음
	StartLevel();
}

int32 ARSGameState::GetScore() const
{
	return Score;
}

void ARSGameState::AddScore(int32 Amount)
{
	Score += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
}

void ARSGameState::StartLevel()
{
	// 밤 시작: 조명을 어둡게 하는 로직을 여기에 넣으면 좋습니다.
	UpdateWorldLighting(0.0f); // 밤이 됨 (Intensity 0)
	MonsterCount = 0;
	KillMonsterCount = 0;

	TArray<AActor*> FoundVolume;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSMonsterSpawnVolume::StaticClass(), FoundVolume);

	// 레벨별 몬스터 수 조절 로직
	const int32 MonsterToSpawn = 1 + CurrentLevelIndex;
	if (FoundVolume.Num() > 0)
	{
		ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(FoundVolume[0]);
		if (SpawnVolume)
		{
			for (int32 i = 0; i < MonsterToSpawn; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnNextMonster();
				// 스폰된 액터가 몬스터인지 확인하여 카운트 업
				if (SpawnedActor && SpawnedActor->IsA(ARSMonster::StaticClass()))
				{
					MonsterCount++;
					//UE_LOG(LogTemp, Warning, TEXT("Level %d Night Start! Spawned: %d"), CurrentLevelIndex + 1, MonsterCount);
					// 몬스터 사망 시 OnMonsterDestroyed가 호출되도록 몬스터 클래스에서 처리 필요
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Level %d Night Start! Total Monsters: %d"), CurrentLevelIndex + 1, MonsterCount);
}

void ARSGameState::OnMonsterKilled()
{
	KillMonsterCount++;

	// 로그에 현재 진행 상황 출력
	UE_LOG(LogTemp, Warning, TEXT("Monster Killed: %d / %d"), KillMonsterCount, MonsterCount);

	// 모든 몬스터를 다 잡았다면 낮으로 전환
	if (KillMonsterCount >= MonsterCount && MonsterCount > 0)
	{
		EndLevelAndReward();
	}
}




void ARSGameState::EndLevelAndReward()
{
	// 낮 시작: 해가 뜨는 연출(조명 Intensity 조절)을 여기에 넣으세요.
	UpdateWorldLighting(3.0f); // 해가 뜸 (Intensity 3)
	UE_LOG(LogTemp, Warning, TEXT("Level %d Clear! Sun is rising..."), CurrentLevelIndex + 1);

	UWorld* World = GetWorld();
	if (!World) return;

	// 레벨별 보상 개수 설정
	// Level 1: 조명탄 10, 수류탄 20
	// Level 2: 조명탄 20, 수류탄 30 ...
	int32 FlareToSpawn = 10 + (CurrentLevelIndex * 10);
	int32 GrenadeToSpawn = 20 + (CurrentLevelIndex * 10);

	FActorSpawnParameters SpawnParams;

	// 조명탄 스폰
	for (int32 i = 0; i < FlareToSpawn; i++)
	{
		FVector RandomLoc = RewardSpawnLocation + FVector(FMath::RandRange(-500.f, 500.f), FMath::RandRange(-500.f, 500.f), 0.f);
		World->SpawnActor<AActor>(FlareClass, RandomLoc, FRotator::ZeroRotator, SpawnParams);
	}

	// 수류탄 스폰
	for (int32 i = 0; i < GrenadeToSpawn; i++)
	{
		FVector RandomLoc = RewardSpawnLocation + FVector(FMath::RandRange(-500.f, 500.f), FMath::RandRange(-500.f, 500.f), 0.f);
		World->SpawnActor<AActor>(GrenadeClass, RandomLoc, FRotator::ZeroRotator, SpawnParams);
	}

	// 다음 레벨 준비 (예: 20초 뒤에 다시 밤이 됨)
	CurrentLevelIndex++;
	GetWorldTimerManager().SetTimer(LevelTransitionTimer, this, &ARSGameState::StartLevel, 50.0f, false);
}

void ARSGameState::UpdateWorldLighting(float NewIntensity)
{
	if (MainLight && MainLight->GetLightComponent())
	{
		MainLight->GetLightComponent()->SetIntensity(NewIntensity);
	}
}

void ARSGameState::FindMainLight()
{
	for (TActorIterator<ADirectionalLight> It(GetWorld()); It; ++It)
	{
		MainLight = *It;
		break; // 첫 번째 디렉셔널 라이트를 찾으면 중단
	}
}

