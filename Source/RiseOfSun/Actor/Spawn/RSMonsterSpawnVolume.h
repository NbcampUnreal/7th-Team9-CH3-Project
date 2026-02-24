#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSMonsterSpawnVolume.generated.h"

class ARSMonster;
struct FMonsterSpawnRow;

UCLASS()
class RISEOFSUN_API ARSMonsterSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSMonsterSpawnVolume();
	
	virtual void BeginPlay() override;
	// 스폰 볼륨의 중심
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	// 몬스터 생성 범위
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;
	// 어떤 몬스터를 스폰할 지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* MonsterDataTable;
	// 최대 몬스터 수
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 MaxSpawnCount = 30;
	// 순차적으로 스폰해주는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnNextMonster();
	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);
	// 몬스터 정보를 하나 선택하는 함수
	FMonsterSpawnRow* GetRandomMonster() const;
	// 전달받은 몬스터 클래스를 실제 월드에 생성하는 함수
	void SpawnMonster(TSubclassOf<ARSMonster> MonsterClass);
	// 몬스터가 생성될 좌표를 정함
	FVector GetRandomPointVolume() const;
	

protected:
	// 몬스터 수
	int32 SpawnCount = 0;
	// 현재 어떤 인덱스를 스폰할지 저장
	int32 CurrentSpawnIndex = 0;
	// 데이터 테이블의 내용을 미리 복사해둘 배열
	TArray<FMonsterSpawnRow*> CachedMonsterRows;
	
	FTimerHandle SpawnTimerHandle;
	// 현재 살아있는 몬스터
	int32 ActiveMonsterCount = 0;
	// 레벨
	int32 CurrentLevel = 1;
	// 레벨업
	void LevelUp();
};
