

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "RSGameState.generated.h"
/**
 * 
 */
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;

	// --- 보상 관련 추가 ---
	UPROPERTY(EditAnywhere, Category = "Reward")
	TSubclassOf<AActor> FlareClass; // 에디터에서 조명탄 할당

	UPROPERTY(EditAnywhere, Category = "Reward")
	TSubclassOf<AActor> GrenadeClass; // 에디터에서 수류탄 할당

	UPROPERTY(EditAnywhere, Category = "Reward")
	FVector RewardSpawnLocation; // 아이템이 떨어질 중심 좌표

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	void StartLevel();// 밤 시작 로직

	void EndLevelAndReward();// 낮 시작 및 보상 로직

	// 몬스터 클래스에서 호출할 함수
	void OnMonsterKilled();


protected:
	// 월드의 메인 조명을 저장할 변수
	UPROPERTY()
	ADirectionalLight* MainLight;

	// 조명 강도를 부드럽게 혹은 즉시 조절할 함수
	void UpdateWorldLighting(float NewIntensity);

	// BeginPlay에서 라이트를 찾는 함수
	void FindMainLight();

	FTimerHandle LevelTransitionTimer;
};
