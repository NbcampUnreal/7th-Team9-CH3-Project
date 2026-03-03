#include "Actor/Character/RSBossMonster.h"
#include "Controller/RSMonsterController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/RSMonsterWidget.h"
#include "Actor/Character/Controller/RSMonsterController.h"
#include "Component/RSBossMonsterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARSBossMonster::ARSBossMonster()
{
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));

	RockMesh->SetupAttachment(GetMesh(), TEXT("Rock")); // 내가만든  소켓
	RockMesh->SetVisibility(false); // 기본은 안 보이게
	RockMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//원기리 공격 쿨타임
	AttackInterval = 7.0f;
}

void ARSBossMonster::ShowRock()
{
	if (RockMesh)
	{
		RockMesh->SetVisibility(true);
	}
}

void ARSBossMonster::HideRock()
{
	if (RockMesh)
	{
		RockMesh->SetVisibility(false);
	}
}

void ARSBossMonster::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Boss BeginPlay Called"));
	
	//몬스터의 기본 속력
	GetCharacterMovement()->MaxWalkSpeed = NormalMovementSpeed;

	if (HPWidgetComponent)
	{
		UUserWidget* Widget = HPWidgetComponent->GetUserWidgetObject();
		if (Widget)
		{
			// 만든 몬스터 HP 위젯 클래스로 캐스팅
			URSMonsterWidget* HPWidget = Cast<URSMonsterWidget>(Widget);
			if (HPWidget)
			{
				HPWidget->SetOwnerMonster(this);
			}
		}
	}
	//원거리 공격을 몇 초마다 실행하는지
	GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&ARSBossMonster::RangedAttack,
		AttackInterval,
		true,
		0.0f
		);
}

int32 ARSBossMonster::HitDamage(int32 DamageAmount)
{
	if (bIsDead)
	{
		return 0;
	}
	int32 Damage = Super::HitDamage(DamageAmount);
	
	return Damage;
}

void ARSBossMonster::RangedAttack()
{
	if (bIsDead)
	{
		return;
	}
	
	ARSMonsterController* AI = Cast<ARSMonsterController>(GetController());
	if (AI)
	{
		AI->StopMovement();
		GetCharacterMovement()->DisableMovement();
	}
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (RangedAttackMontage && AnimInstance)
	{
		AnimInstance->Montage_Play(RangedAttackMontage);
	}
}

void ARSBossMonster::Die()
{
	if (bIsDead)
	{
		return;
	}
	
	Super::Die();
	
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
}

void ARSBossMonster::FireProjectile()
{
	if (!ProjectileClass)
	{
		return;
	}
	
	ARSPlayer* Player = Cast<ARSPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player)
	{
		return;
	}
	FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("Rock"));

	FVector TossVelocity;

	bool bSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		SpawnLocation,
		Player->GetActorLocation(),
		5000.f,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!bSuccess) return;

	FRotator SpawnRotation = TossVelocity.Rotation();

	ARSBossMonsterProjectile* Projectile =
		GetWorld()->SpawnActor<ARSBossMonsterProjectile>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation
		);

	if (Projectile)
	{
		Projectile->GetProjectileMovement()->Velocity = TossVelocity;
	}
}

void ARSBossMonster::OnRangedAttackEnd()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCharacterMovement()->MaxWalkSpeed = NormalMovementSpeed;
}