#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "Components/WidgetComponent.h"
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
	virtual FDamageResult Attack(ARSCharacter* Target) override;;

	float GetAttackRange() const { return AttackRange; }

protected:
	virtual void BeginPlay() override;
	
private:
	float AttackRange;
	float MonsterDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HPWidgetComponent;


	UPROPERTY(EditAnywhere, Category = "AttackAnim")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "DieAnim")
	class UAnimMontage* DieMontage;
};