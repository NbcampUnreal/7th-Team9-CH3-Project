#pragma once

#include "CoreMinimal.h"
#include "RSStat.h"
#include "GameFramework/Character.h"
#include "RSCharacter.generated.h"

// 데미지 결과
USTRUCT()
struct FDamageResult
{
	GENERATED_BODY()

	int32 Damage;
	ACharacter* Attacker;
	ACharacter* Target;
};	

UCLASS()
class RISEOFSUN_API ARSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARSCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Stat")
	FRSStat Stat;
	// 공격 
	virtual FDamageResult Attack(ARSCharacter* Target);
	// 받는 피해
	int32 HitDamage(int32 DamageAmount);
};
