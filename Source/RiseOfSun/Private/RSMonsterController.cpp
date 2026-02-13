#include "RSMonsterController.h"
#include "Kismet/GameplayStatics.h"

ARSMonsterController::ARSMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARSMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			TargetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

			ChangeState(AIState::Chase);
		});
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
		TickAttack(DeltaTime);
		break;
	}
}
void ARSMonsterController::ChangeState(AIState NewState)
{
	CurrentState = NewState;

	if (NewState == AIState::Chase)
	{

		if (TargetPlayer)
		{
			const auto Result = MoveToActor(TargetPlayer, AttackRadius);
		}
	}

	switch (NewState)
	{
	case AIState::Chase:
		if (TargetPlayer)
		{
			const EPathFollowingRequestResult::Type Result =
				MoveToActor(TargetPlayer, AttackRadius);
		}
		break;

	case AIState::Attack:
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
	}
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