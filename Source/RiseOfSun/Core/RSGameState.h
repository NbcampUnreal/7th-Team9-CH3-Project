#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "RSGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnZombieChanged, int32, KillMonsterCount, int32, MonsterCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, CurrentLevelIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChanged, FTimerHandle, LevelTransitionTimer);

 // 클래스 전방 선언 (헤더가 무거워지는 것을 방지)
class ADirectionalLight;

UCLASS()
class RISEOFSUN_API ARSGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ARSGameState();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	int32 MonsterCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	int32 KillMonsterCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	int32 MaxMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;

	FOnZombieChanged OnZombieChanged;

	FOnLevelChanged OnLevelChanged;

	FOnTimerChanged OnTimerChanged;

	// --- 보상 관련 추가 ---
	UPROPERTY(EditAnywhere, Category = "Reward")
	TSubclassOf<AActor> FlareClass; // 에디터에서 조명탄 할당

	UPROPERTY(EditAnywhere, Category = "Reward")
	TSubclassOf<AActor> GrenadeClass; // 에디터에서 수류탄 할당

	UPROPERTY(EditAnywhere, Category = "Reward")
	FVector RewardSpawnLocation; // 아이템이 떨어질 중심 좌표

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	int32 GetCurrentLevelIndex() { return CurrentLevelIndex; }

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	void StartLevel();// 밤 시작 로직

	void EndLevelAndReward();// 낮 시작 및 보상 로직

	// 몬스터 클래스에서 호출할 함수
	void OnMonsterKilled();

	//보스몬스터 호출 함수
	void SpawnBossMonster();
	
	//보스몬스터를 죽일 시 호출하는 함수
	void OnBossKilled();
	
	UFUNCTION()
	void SpawnOneMonster();

	UPROPERTY()
	bool CurrentState;
	
	//보스가 소환되었는지 체크
	bool bIsBossSpawned = false;

	FTimerHandle MonsterSpawnTimerHandle;

	FTimerHandle LevelTransitionTimer;

protected:
	// 월드의 메인 조명을 저장할 변수
	UPROPERTY()
	ADirectionalLight* MainLight;

	// 조명 강도를 부드럽게 혹은 즉시 조절할 함수
	void UpdateWorldLighting(float NewIntensity);

	// BeginPlay에서 라이트를 찾는 함수
	void FindMainLight();
	
	//블루프린트에서 보스 몬스터 클래스 할당
	UPROPERTY(EditAnywhere, Category = "BossMonster")
	TSubclassOf<class ARSBossMonster>BossMonsterClass;

	
};
