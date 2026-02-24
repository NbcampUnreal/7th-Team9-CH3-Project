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
	
	UPROPERTY()
	ACharacter* Attacker;
	
	UPROPERTY()
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
	bool bIsDead = false;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Die();
	//죽었나 확인
	bool IsDead() { return Stat.CurrentHealth <= 0; }

	// 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Stat")
	FRSStat Stat;

	// 공격 
	virtual FDamageResult Attack(ARSCharacter* Target);

	// 받는 피해
	int32 HitDamage(int32 DamageAmount);

	//현재 HP와 최대 HP를 반환하는 함수
	UFUNCTION(BlueprintPure)
	float GetCurrentHP() const { return Stat.CurrentHealth; }

	UFUNCTION(BlueprintPure)
	float GetMaxHP() const { return Stat.MaxHealth; }
};
