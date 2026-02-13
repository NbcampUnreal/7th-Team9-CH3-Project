#pragma once

#include "CoreMinimal.h"
#include "RSMonster.h"
#include "MonsterSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    // 몬스터 고유 이름 (데이터 식별용)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MonsterName;
    // 실제로 스폰될 몬스터 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ARSMonster> MonsterClass;
    //몬스터 스폰 확률
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance;
};
