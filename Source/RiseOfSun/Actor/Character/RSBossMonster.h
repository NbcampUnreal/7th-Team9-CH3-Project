#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/RSMonster.h"
#include "RSBossMonster.generated.h"

/**
 * 
 */
UCLASS()
class RISEOFSUN_API ARSBossMonster : public ARSMonster
{
	GENERATED_BODY()
	
public:
	ARSBossMonster();
	virtual void BeginPlay() override;
	virtual int32 HitDamage(int32 DamageAmount)override;
};
