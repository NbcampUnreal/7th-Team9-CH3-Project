#pragma once

#include "CoreMinimal.h"
#include "RSCharacter.h"
#include "Components/WidgetComponent.h"
#include "RSMonster.generated.h"

class USphereComponent;
class AController;
class AActor;
class ARSPlayer;

UCLASS()
class RISEOFSUN_API ARSMonster : public ARSCharacter
{
	GENERATED_BODY()
	
public:
	ARSMonster();

	// 데미지 UI 표시
	UFUNCTION()
	void ShowDamageUI();

	UFUNCTION()
	void HideDamageUI();
	
	//몬스터를 느려지게하는 효과
	void SlowEffect();
	
	//느려진 몬스터의 속도를 회복
	void RestoreSpeed();
	
	// 몬스터 범위 내 플레이어가 있는지
	bool CanAttack(ACharacter* Target);
	virtual FDamageResult Attack(ARSCharacter* Target) override;;
	//몬스터가 피해를 입으면 발동하는 효과
	virtual void DamageEffect() override;
	
	float GetAttackRange() const { return AttackRange; }

	//몬스터의 기본 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float NormalMovementSpeed = 400.f;
	//몬스터의 이동속도 감소 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SlowMovementSpeed = 200.f;
	//몬스터의 이동속도 감소 지속시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SlowDuration = 1.f;
	
	//이동속도 회복 타이머
	FTimerHandle SlowTimerHandle;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	float AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HPWidgetComponent;


	UPROPERTY(EditAnywhere, Category = "AttackAnim")
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = "DieAnim")
	class UAnimMontage* DieMontage;

	// 추가: 데미지 UI 타이머 핸들
	FTimerHandle DamageUITimerHandle;

};