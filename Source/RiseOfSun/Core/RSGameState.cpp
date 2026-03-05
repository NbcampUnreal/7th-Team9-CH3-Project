

#include "RSGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Spawn/RSMonsterSpawnVolume.h"
#include "Actor/Spawn/RSItemSpawnVolume.h"
#include "Actor/Character/RSMonster.h"
#include "EngineUtils.h"
#include "Actor/Character/RSBossMonster.h"
#include "RSGameMode.h"
#include "Actor/Character/Controller/RSPlayerController.h"

ARSGameState::ARSGameState()
{
	Score = 0;
	MonsterCount = 0;
	KillMonsterCount = 0;
	CurrentLevelIndex = 1;
	RewardSpawnLocation = FVector(0.f, 0.f, 100.f);
	CurrentState = true;
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
	if (CurrentState == false)
	{
		return;
	}

	CurrentState = false;

	// 밤 시작: 조명을 어둡게 하는 로직을 여기에 넣으면 좋습니다.
	UpdateWorldLighting(0.0f); // 밤이 됨 (Intensity 0)
	MonsterCount = 0;
	KillMonsterCount = 0;

	/*TArray<AActor*> FoundVolume;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSMonsterSpawnVolume::StaticClass(), FoundVolume);*/
	//-----------------------------------------------------------------------------------------------------
	// --- 추가: 밤이 되면 스폰 볼륨을 다시 켭니다 ---
	//for (AActor* VolumeActor : FoundVolume)
	//{
	//	ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(VolumeActor);
	//	if (SpawnVolume)
	//	{
	//		SpawnVolume->SetIsSpawning(true);
	//		SpawnVolume->ResetSpawnCount();
	//	}
	//}
	//// 레벨별 몬스터 수 조절 로직
	//const int32 MonsterToSpawn = (CurrentLevelIndex + 1) * 10;
	//if (FoundVolume.Num() > 0)
	//{
	//	ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(FoundVolume[0]);
	//	if (SpawnVolume)
	//	{
	//		for (int32 i = 0; i < MonsterToSpawn; i++)
	//		{
	//			AActor* SpawnedActor = SpawnVolume->SpawnNextMonster();
	//			// 스폰된 액터가 몬스터인지 확인하여 카운트 업
	//			if (SpawnedActor && SpawnedActor->IsA(ARSMonster::StaticClass()))
	//			{
	//				MonsterCount++;
	//				UE_LOG(LogTemp, Warning, TEXT("Level %d Night Start! Spawned: %d"), CurrentLevelIndex,MonsterCount);
	//				// 몬스터 사망 시 OnMonsterDestroyed가 호출되도록 몬스터 클래스에서 처리 필요
	//			}
	//		}
	//	}
	//}

	/*if (FoundVolume.Num() > 0)
	{
		ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(FoundVolume[0]);
		if (SpawnVolume)
		{
			SpawnVolume->SetIsSpawning(true);
			SpawnVolume->ResetSpawnCount();

			const int32 MonsterToSpawn = (CurrentLevelIndex + 1) * 10;

			for (int32 i = 0; i < MonsterToSpawn; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnNextMonster();
				if (SpawnedActor && SpawnedActor->IsA(ARSMonster::StaticClass()))
				{
					MonsterCount++;
				}
			}
		}
	}*/

	MaxMonster = (CurrentLevelIndex) * 10;

	OnZombieChanged.Broadcast(KillMonsterCount, MaxMonster);
	OnLevelChanged.Broadcast(CurrentLevelIndex);

	GetWorldTimerManager().SetTimer(MonsterSpawnTimerHandle, this, &ARSGameState::SpawnOneMonster, 1.0f, true);

	UE_LOG(LogTemp, Warning, TEXT("Level %d Night Start! Total Monsters: %d"), CurrentLevelIndex + 1, MonsterCount);
}

void ARSGameState::OnMonsterKilled()
{
	KillMonsterCount++;

	OnZombieChanged.Broadcast(KillMonsterCount, MaxMonster);

	//2레벨까지는 몬스터를 다 잡으면 넘어감
	if (CurrentLevelIndex < 3)
	{
		// 모든 몬스터를 다 잡았다면 낮으로 전환
		if (KillMonsterCount >= MaxMonster)
		{
			EndLevelAndReward();
		}
	}
}

void ARSGameState::SpawnOneMonster()
{
	if (MonsterCount >= MaxMonster)
	{
		GetWorldTimerManager().ClearTimer(MonsterSpawnTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("All monsters spawned for this level."));
		return;
	}
	
	//레벨인덱스가 2이고, 보스몬스터가 소환되지 않았다면 실행
	if (CurrentLevelIndex == 3 && !bIsBossSpawned)
	{
		SpawnBossMonster();
		
		bIsBossSpawned = true;
	}

	TArray<AActor*> FoundVolume;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSMonsterSpawnVolume::StaticClass(), FoundVolume);

	if (FoundVolume.Num() > 0)
	{
		int32 RandomIdx = FMath::RandRange(0, FoundVolume.Num() - 1);
		ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(FoundVolume[RandomIdx]);
		if (SpawnVolume)
		{
			SpawnVolume->SetIsSpawning(true);
			SpawnVolume->ResetSpawnCount();

			// 한 마리 소환
			AActor* SpawnedActor = SpawnVolume->SpawnNextMonster();
			if (SpawnedActor && SpawnedActor->IsA(ARSMonster::StaticClass()))
			{
				MonsterCount++;
				// 소환될 때마다 UI 갱신 (선택 사항: 숫자가 올라가는 게 보임)
				OnZombieChanged.Broadcast(KillMonsterCount, MonsterCount);
			}
		}
	}
}

void ARSGameState::EndLevelAndReward()
{
	if (CurrentState == true)
	{
		return;
	}

	CurrentState = true;

	// 낮 시작: 해가 뜨는 연출(조명 Intensity 조절)을 여기에 넣으세요.
	UpdateWorldLighting(3.0f); // 해가 뜸 (Intensity 3)
	UE_LOG(LogTemp, Warning, TEXT("Level %d Clear! Sun is rising..."), CurrentLevelIndex + 1);


	//살아남은 모든 몬스터 제거
	//해가 뜨면 남아있는 몬스터들을 타 죽거나 사라짐
	// --- 추가: 해가 뜨면 스폰 볼륨을 끕니다 ---
	TArray<AActor*> FoundVolume;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSMonsterSpawnVolume::StaticClass(), FoundVolume);
	for (AActor* VolumeActor : FoundVolume)
	{
		ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(VolumeActor);
		if (SpawnVolume)
		{
			SpawnVolume->SetIsSpawning(false);
		}
	}
	// ------------------------------------------
	
	for (TActorIterator<ARSMonster> It(GetWorld()); It; ++It)
	{
		
		if (ARSMonster* RemainingMonster = *It)
		{
			RemainingMonster->Die();//몬스터 즉시 제거
		}
	}
	// 다음 레벨 준비 (예: 60초 뒤에 다시 밤이 됨)
	CurrentLevelIndex++;
	OnLevelChanged.Broadcast(CurrentLevelIndex);
	if (CurrentLevelIndex > 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("모든 레벨 클리어! 게임을 종료합니다."));
		if (AGameModeBase* GameMode = GetWorld()->GetAuthGameMode())
		{
			ARSGameMode* RSGaneMode = Cast<ARSGameMode>(GameMode);
			if (RSGaneMode)
			{
				RSGaneMode->GameClear();
				ARSPlayerController* playerController = Cast<ARSPlayerController>(GetWorld()->GetFirstPlayerController());
				if (playerController)
				{
					playerController->bShowMouseCursor = true;
					playerController->SetPause(true);
				}
			}
		}
		// 여기에 승리 UI 표시 기능을 넣으면 좋습니다.
		return; // 더 이상 아래의 아이템 생성과 타이머를 실행하지 않고 끝냅니다.
	}

	UWorld* World = GetWorld();
	if (!World) return;
	TArray<AActor*> FoundItemVolumes; // 변수 선언
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSItemSpawnVolume::StaticClass(), FoundItemVolumes);
	// 레벨별 보상 개수 설정
	// Level 1: 조명탄 10, 수류탄 20
	// Level 2: 조명탄 20, 수류탄 30 ...
	if (FoundItemVolumes.Num() > 0)
	{
		// 레벨별 개수 설정 (0번 인덱스가 레벨 1이므로 이미 10, 20... 으로 계산됨)
		int32 FlareToSpawn = CurrentLevelIndex + 3;
		int32 GrenadeToSpawn = CurrentLevelIndex +2;

		// 조명탄 스폰 요청
		for (int32 i = 0; i < FlareToSpawn; i++)
		{
			int32 Rnd = FMath::RandRange(0, FoundItemVolumes.Num() - 1);
			ARSItemSpawnVolume* Vol = Cast<ARSItemSpawnVolume>(FoundItemVolumes[Rnd]);
			if (Vol)
			{
				Vol->SpawnItem(FlareClass);
			}// 볼륨에게 스폰을 시킴
		}

		// 수류탄 스폰 요청
		for (int32 i = 0; i < GrenadeToSpawn; i++)
		{
			int32 Rnd = FMath::RandRange(0, FoundItemVolumes.Num() - 1);
			ARSItemSpawnVolume* Vol = Cast<ARSItemSpawnVolume>(FoundItemVolumes[Rnd]);
			if (Vol)
			{
				Vol->SpawnItem(GrenadeClass);// 볼륨에게 스폰을 시킴
			}
		}
		for (int32 i = 0; i < GrenadeToSpawn; i++)
		{
			int32 Rnd = FMath::RandRange(0, FoundItemVolumes.Num() - 1);
			ARSItemSpawnVolume* Vol = Cast<ARSItemSpawnVolume>(FoundItemVolumes[Rnd]);
			if (Vol)
			{
				Vol->SpawnItem(HealClass);// 볼륨에게 스폰을 시킴
			}
		}
	}
	else
	{
		// 만약 볼륨이 하나도 없으면 경고 로그를 남깁니다.
		UE_LOG(LogTemp, Error, TEXT("월드에 ARSItemSpawnVolume이 배치되지 않았습니다!"));
	}

	GetWorldTimerManager().SetTimer(LevelTransitionTimer, this, &ARSGameState::StartLevel, 60.0f, false);
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

void ARSGameState::SpawnBossMonster()
{
	if (!BossMonsterClass)
	{
		return;
	}
	//맵에 있는 스폰볼륨 찾기
	TArray<AActor*> FoundVolume;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARSMonsterSpawnVolume::StaticClass(), FoundVolume);
	
	if (FoundVolume.Num() > 0)
	{
		//맵에 있는 스폰볼륨 중 하나 선택
		int32 RandomIdx = FMath::RandRange(0, FoundVolume.Num() - 1);
		ARSMonsterSpawnVolume* SpawnVolume = Cast<ARSMonsterSpawnVolume>(FoundVolume[RandomIdx]);
		
		if (SpawnVolume)
		{
			//선택된  스폰볼륨의 위치와 회전값 가져오기
			FVector SpawnLocation = SpawnVolume->GetActorLocation();
			FRotator SpawnRotation = SpawnVolume->GetActorRotation();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			//보스몬스터 스폰
			ARSBossMonster* BossMonster = GetWorld()->SpawnActor<ARSBossMonster>(BossMonsterClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}

void ARSGameState::OnBossKilled()
{
	EndLevelAndReward();
}
