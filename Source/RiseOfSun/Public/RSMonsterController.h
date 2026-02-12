#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TimerManager.h"
#include "RSMonsterController.generated.h"

UENUM(BlueprintType)
enum class AIState : uint8
{
	Idle,
	Patrol,
	Chase,
	Attack
};

UCLASS()
class RISEOFSUN_API ARSMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	ARSMonsterController();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	AIState CurrentState = AIState::Idle;
	void ChangeState(AIState NewState);

	void TickChase(float DeltaTime);
	void TickAttack(float DeltaTime);

	UPROPERTY()
	APawn* TargetPlayer = nullptr;

	float AttackRange = 50.0f;
	float AttackRadius = 5.f;

	bool IsPlayerInRange(float Range) const;
};
