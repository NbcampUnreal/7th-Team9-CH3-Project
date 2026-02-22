// Fill out your copyright notice in the Description page of Project Settings.


#include "RSCharacter.h"
#include "RSMonster.h"


ARSCharacter::ARSCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	Stat.CurrentHealth = Stat.MaxHealth;
}

// Called when the game starts or when spawned
void ARSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARSCharacter::Die()
{
	if(bIsDead)
		return;
	
	bIsDead = true;
	this->Destroy();

}

FDamageResult ARSCharacter::Attack(ARSCharacter* Target)
{	// Target이 없으면 리턴
	if (!IsValid(Target))
	{
		return FDamageResult();
	}

	int32 Damage = Stat.AttackDamage;
	int32 FinalDamage = Target->HitDamage(Damage);
	FDamageResult result;
	result.Attacker = this;
	result.Target = Target;
	result.Damage = FinalDamage;

	return result;
}

int32 ARSCharacter::HitDamage(int32 DamageAmount)
{
	int32 Damage = DamageAmount - Stat.Defense;
	Damage = std::max(Damage, 0);

	Stat.CurrentHealth -= Damage;
	Stat.CurrentHealth = std::max(Stat.CurrentHealth, 0.0f);

	// 데미지를 몬스터가 받는다면 UI 띄우기
	if (Damage > 0)
		{
			ARSMonster* Monster = Cast<ARSMonster>(this);
			if (Monster)
			{
				// 공격자 여부 상관없이 데미지가 들어오면 UI 표시
				Monster->ShowDamageUI();
			}
		}
	return Damage;
}

