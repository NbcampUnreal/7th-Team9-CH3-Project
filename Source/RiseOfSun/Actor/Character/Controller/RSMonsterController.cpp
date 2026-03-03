#include "RSMonsterController.h"

#include "Actor/Character/RSBossMonster.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Character/RSMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

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

		SetChangeState(AIState::Chase);
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

static const TCHAR* StateToText(AIState S)
{
	switch (S)
	{
	case AIState::Chase: return TEXT("Chase");
	case AIState::Attack: return TEXT("Attack");
	default: return TEXT("Unknown");
	}
}

void ARSMonsterController::SetChangeState(AIState NewState)
{
	if (CurrentState == NewState)
		return;

	AIState OldState = CurrentState;
	CurrentState = NewState;

	//UE_LOG(LogTemp, Display, TEXT("[AI] State: %s -> %s"),StateToText(OldState), StateToText(NewState));

	if (NewState == AIState::Chase)
	{
		//UE_LOG(LogTemp, Warning, TEXT("[AI] ENTER CHASE"));
	}
	else if (NewState == AIState::Attack)
	{
		//UE_LOG(LogTemp, Warning, TEXT("[AI] ENTER ATTACK"));
	}

	if (NewState == AIState::Attack)
	{
		//UE_LOG(LogTemp, Warning, TEXT("State changed: %d -> %d (ENTER ATTACK)"),(int32)OldState, (int32)NewState);
	}

	switch (NewState)
	{
	case AIState::Chase:
		if (TargetPlayer)
		{
			ARSMonster* Monster = Cast<ARSMonster>(GetPawn());
			if (!Monster)
			{
				return;
			}
			float Range = Monster->GetAttackRange();
		}
		break;

	case AIState::Attack:
		StopMovement();
		break;
	}
}


void ARSMonsterController::TickChase(float DeltaTime)
{
	if (!TargetPlayer)
	{
		return;
	}

	ARSMonster* Monster = Cast<ARSMonster>(GetPawn());
	if (!Monster)
	{
		return;
	}

	float AttackRange = 10.f;
	float Range = Monster->GetAttackRange();
	//UE_LOG(LogTemp, Warning, TEXT("Range=%.1f"), Range);

	const float Dist = FVector::Dist(
		GetPawn()->GetActorLocation(),
		TargetPlayer->GetActorLocation()
	);


	if (Dist <= Range)
	{
		//UE_LOG(LogTemp, Warning, TEXT("IN RANGE -> TRY ATTACK"));
	}

	if (IsPlayerInRange(Range))
	{
		SetChangeState(AIState::Attack);
		return;
	}

	auto Result = MoveToActor(TargetPlayer, AttackRange);
}

void ARSMonsterController::TickAttack(float DeltaTime)
{
	ARSMonster* Monster = Cast<ARSMonster>(GetPawn());
	if (!Monster) return;

	const float Range = Monster->GetAttackRange();
	if (!IsPlayerInRange(Range))
	{
		SetChangeState(AIState::Chase);
		return;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();

	ARSCharacter* AttackTargetPlayer = Cast<ARSCharacter>(TargetPlayer);
	if (!AttackTargetPlayer) return;


	if (Monster->CanAttack(AttackTargetPlayer) && CurrentTime - LastAttackTime >= AttackCooldown)
	{
		Monster->Attack(AttackTargetPlayer);
		LastAttackTime = CurrentTime;
	}
}

bool ARSMonsterController::IsPlayerInRange(float Range) const
{
	if (!TargetPlayer || !GetPawn()) return false;

	const FVector P = GetPawn()->GetActorLocation();
	const FVector T = TargetPlayer->GetActorLocation();

	const float Dist3D = FVector::Dist(P, T);
	const float Dist2D = FVector::Dist2D(P, T);
	const float DeltaZ = FMath::Abs(P.Z - T.Z);

	return Dist3D <= Range;
}
