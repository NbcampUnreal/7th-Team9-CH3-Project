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

	// 몬스터 범위 내 플레이어가 있는지
	bool CanAttack(ACharacter* Target);
	virtual FDamageResult Attack(ARSCharacter* Target) override;;

	float GetAttackRange() const { return AttackRange; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	float AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HPWidgetComponent;

	// 추가: 데미지 UI 타이머 핸들
	FTimerHandle DamageUITimerHandle;
};