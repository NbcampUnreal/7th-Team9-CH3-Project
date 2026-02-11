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
	

	//몬스터 공격
	void Attack(AActor* Target);

};
