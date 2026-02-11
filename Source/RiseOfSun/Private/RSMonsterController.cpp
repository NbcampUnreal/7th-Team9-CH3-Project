#include "RSMonsterController.h"
#include "Kismet/GameplayStatics.h"

ARSMonsterController::ARSMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARSMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TargetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ChangeState(AIState::Chase);
}

void ARSMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case AIState::Chase:
		TickChase(DeltaTime);
		break;
	case AIState::Attack:
		TickChase(DeltaTime);
		break;
	}
}
void ARSMonsterController::ChangeState(AIState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	switch (NewState)
	{
	case AIState::Chase:
		if (TargetPlayer)
		{
			MoveToActor(TargetPlayer, AttackRange);
		}
		break;
	case AIState::Attack:
		StopMovement();
		break;
	default:
		StopMovement();
		break;
	}
}

void ARSMonsterController::TickChase(float DeltaTime)
{
	if (TargetPlayer == nullptr)
	{
		return;
	}

	if (IsPlayerInRange(AttackRange))
	{
		ChangeState(AIState::Attack);
		return;
	}

	MoveToActor(TargetPlayer, AttackRange);
}

void ARSMonsterController::TickAttack(float DeltaTime)
{
	
}

bool ARSMonsterController::IsPlayerInRange(float Range) const
{
	if (TargetPlayer == nullptr || GetPawn() == nullptr)
	{
		return false;
	}

	const float Distance = FVector::Dist(
		GetPawn()->GetActorLocation(),
		TargetPlayer->GetActorLocation());
	
	return Distance <= Range;
}