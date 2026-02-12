#include "RSMonster.h"
#include "RSPlayer.h"

ARSMonster::ARSMonster()
{
    AttackRange = 200.0f;
    MonsterDamage = 10.0f;
}

bool ARSMonster::CanAttack(ACharacter* Target)
{
    FVector ActorLocation = GetActorLocation();  //몬스터 위치
    FVector PlayerLocation = Target->GetActorLocation();  //플레이어 위치
    const float DistSq = FVector::DistSquared(ActorLocation, PlayerLocation);
    
    return DistSq <= AttackRange * AttackRange; // 공격범위
}

void ARSMonster::Attack(ACharacter* Target)
{
    if (!CanAttack(Target)) return;
    
    //Target->TakeDamage(MonsterDamage);
}
