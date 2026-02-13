#pragma once

#include "CoreMinimal.h"
#include "MonsterSpawnRow.h"
#include "GameFramework/Actor.h"
#include "RSMonster.h"
#include "RSMonsterSpawnVolume.generated.h"

UCLASS()
class RISEOFSUN_API ARSMonsterSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSMonsterSpawnVolume();
	
	// 스폰 볼륨의 중심
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	// 몬스터 생성 범위
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	class UBoxComponent* SpawningBox;
	// 어떤 몬스터를 스폰할 지
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* MonsterDataTable;
	// 랜덤으로 스폰해주는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomMonster();
	// 몬스터 정보를 하나 선택하는 함수
	FMonsterSpawnRow* GetRandomMonster() const;
	// 전달받은 몬스터 클래스를 실제 월드에 생성하는 함수
	void SpawnMonster(TSubclassOf<ARSMonster> MonsterClass);
	// 몬스터가 생성될 좌표를 정함
	FVector GetRandomPointVolume() const;
};
