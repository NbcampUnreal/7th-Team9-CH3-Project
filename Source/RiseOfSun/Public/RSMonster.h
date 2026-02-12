#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "RSMonster.generated.h"

class USphereComponent;

UCLASS()
class RISEOFSUN_API ARSMonster : public ARSCharacter
{
	GENERATED_BODY()
	
public:
	ARSMonster();

	// 몬스터 범위 내 플레이어가 있는지
	bool CanAttack(ACharacter* Target);

	// 몬스터 공격
	void Attack(ACharacter* Target);

	// 공격 범위
	float AttackRange;
	// 몬스터 데미지
	float MonsterDamage;
};